// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "ItemMasterTableTypes.h"
#include "ItemDBSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSDESIGN_API UItemDBSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const FItemDataRow* GetItemData(FName ItemID) const;

protected :
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemDataTable;
};
