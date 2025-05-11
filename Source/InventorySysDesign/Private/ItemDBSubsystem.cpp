// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDBSubsystem.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

void UItemDBSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	UDataTable* ItemTableFInder = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/DT_ItemMaster.DT_ItemMaster")));
	if(ItemTableFInder)
	{
		ItemDataTable = ItemTableFInder;
	}
}

const FItemDataRow *UItemDBSubsystem::GetItemData(FName ItemID) const
{
    if (!ItemDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("ItemDataTable is NULL!"));
        return nullptr;
    }

    const FItemDataRow* Row = ItemDataTable->FindRow<FItemDataRow>(ItemID, TEXT("LookupItemData"));
    if (!Row)
    {
        UE_LOG(LogTemp, Error, TEXT("FindRow failed for ItemID: %s"), *ItemID.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Item found: %s ¡æ %s"), *ItemID.ToString(), *Row->DisplayName.ToString());
    }

    return Row;
}
