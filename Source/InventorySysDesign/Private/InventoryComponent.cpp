    // Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "ItemBase.h"
#include "ItemDBSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddItem(const FInventoryItem& NewItem)
{
    if (InventoryMap.Contains(NewItem.ItemID))
    {
        InventoryMap[NewItem.ItemID].Quantity += NewItem.Quantity;
    }
    else
    {	
        InventoryMap.Add(NewItem.ItemID, NewItem);
    }
	
	UE_LOG(LogTemp, Log, TEXT("[%s Added] Total Quntitay : %d"), *NewItem.ItemID.ToString(), NewItem.Quantity);

    OnInventoryUpdated.Broadcast();
    return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Count)
{
    if (InventoryMap.Contains(ItemID))
    {
		
        FInventoryItem& Item = InventoryMap[ItemID];
        Item.Quantity -= Count;

        if (Item.Quantity <= 0)
        {
            InventoryMap.Remove(ItemID);
        }

		UE_LOG(LogTemp, Log, TEXT("[%s Remove] Total Quntitay : %d"), *Item.ItemID.ToString(), Item.Quantity);

        OnInventoryUpdated.Broadcast();
        return true;
    }

    return false;
}

int32 UInventoryComponent::GetItemQuantity(FName ItemID) const
{
    if (const FInventoryItem* Found = InventoryMap.Find(ItemID))
    {
        return Found->Quantity;
    }

    return 0;
}

TArray<FInventoryItem> UInventoryComponent::GetInventoryAsArray() const
{
    TArray<FInventoryItem> Result;
    InventoryMap.GenerateValueArray(Result);
    return Result;
}

void UInventoryComponent::DropItem(const FInventoryItem& Item)
{
	if (!GetOwner()) return;

	UE_LOG(LogTemp, Warning, TEXT("[DropItem] Incoming ItemID: %s, Quantity: %d"), *Item.ItemID.ToString(), Item.Quantity);

	// 안전한 Subsystem 접근
	UItemDBSubsystem* ItemDB = nullptr;
	if (const UWorld* World = GetOwner()->GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			ItemDB = GameInstance->GetSubsystem<UItemDBSubsystem>();
		}
	}

	if (!ItemDB) return;

	
	const FItemDataRow* ItemData = ItemDB->GetItemData(Item.ItemID);
	if (!ItemData || !ItemData->ItemClass) return;

	// 스폰 설정
	FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100.f;
	FRotator SpawnRotation = GetOwner()->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	AItemBase* DroppedItem = GetWorld()->SpawnActor<AItemBase>(ItemData->ItemClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (DroppedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("Dropped Item: %s"), *Item.ItemID.ToString());
		RemoveItem(Item.ItemID, 1); // 수량 1 차감
	}
}

void UInventoryComponent::GetQuickSlotItems(TArray<FInventoryItem> &OutQuickSlotItems) const
{
    OutQuickSlotItems.Empty();

    const int32 MaxQuickSlotCount = 10;

    TArray<FInventoryItem> AllItems;
    InventoryMap.GenerateValueArray(AllItems);

    for(int32 i = 0 ; i < FMath::Min(AllItems.Num(), MaxQuickSlotCount) ; i++)
    {
        OutQuickSlotItems.Add(AllItems[i]);

		UE_LOG(LogTemp, Warning, TEXT("[QuickSlot %d] ItemID: %s | Quantity: %d"), i, *OutQuickSlotItems[i].ItemID.ToString(), OutQuickSlotItems[i].Quantity);
    }
}

void UInventoryComponent::GetAllItems(TArray<FInventoryItem> &OutItems) const
{
    InventoryMap.GenerateValueArray(OutItems);
}

void UInventoryComponent::SortItems(TArray<FInventoryItem> &Items, EInventorySortType SortType) const
{
	// Subsystem 접근
	UItemDBSubsystem* ItemDB = nullptr;
	if (const UWorld* World = GetOwner() ? GetOwner()->GetWorld() : nullptr)
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			ItemDB = GameInstance->GetSubsystem<UItemDBSubsystem>();
		}
	}

	if (!ItemDB) return;

	switch (SortType)
	{
		case EInventorySortType::Name:
			Items.Sort([ItemDB](const FInventoryItem& A, const FInventoryItem& B)
			{
				const FItemDataRow* AData = ItemDB->GetItemData(A.ItemID);
				const FItemDataRow* BData = ItemDB->GetItemData(B.ItemID);

				if (!AData || !BData) return false;

				return AData->DisplayName.CompareTo(BData->DisplayName) < 0;
			});
			break;

		case EInventorySortType::Quantity:
			Items.Sort([](const FInventoryItem& A, const FInventoryItem& B)
			{
				return A.Quantity > B.Quantity;
			});
			break;

		case EInventorySortType::ItemType:
			Items.Sort([ItemDB](const FInventoryItem& A, const FInventoryItem& B)
			{
				const FItemDataRow* AData = ItemDB->GetItemData(A.ItemID);
				const FItemDataRow* BData = ItemDB->GetItemData(B.ItemID);

				if (!AData || !BData) return false;

				return static_cast<uint8>(AData->ItemType) < static_cast<uint8>(BData->ItemType);
			});
			break;

		case EInventorySortType::Price:
			Items.Sort([ItemDB](const FInventoryItem& A, const FInventoryItem& B)
			{
				const FItemDataRow* AData = ItemDB->GetItemData(A.ItemID);
				const FItemDataRow* BData = ItemDB->GetItemData(B.ItemID);

				if (!AData || !BData) return false;

				return AData->Price > BData->Price;
			});
			break;
	}
}
