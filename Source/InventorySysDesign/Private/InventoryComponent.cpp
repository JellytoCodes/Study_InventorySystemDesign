// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemBase.h"

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

void UInventoryComponent::DropItem(FName ItemID)
{
	if(!InventoryMap.Contains(ItemID)) return;

    const FInventoryItem& Item = InventoryMap[ItemID];
    if(!Item.ItemClass) return;

    AActor* OwnerActor = GetOwner();
    if(!OwnerActor) return;

    FVector DropLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * 100.f;
    FTransform SpawnTransform(DropLocation);

    GetWorld()->SpawnActor<AItemBase>(Item.ItemClass, SpawnTransform);

    RemoveItem(ItemID, 1);
    UE_LOG(LogTemp, Log, TEXT("[Drop] Item: %s | Quantity : %d"),*Item.ItemID.ToString(), Item.Quantity);
    
    OnInventoryUpdated.Broadcast();
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
    }
}

void UInventoryComponent::GetAllItems(TArray<FInventoryItem> &OutItems) const
{
    InventoryMap.GenerateValueArray(OutItems);
}
