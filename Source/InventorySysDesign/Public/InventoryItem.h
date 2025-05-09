// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

class AItemBase;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Consumable	UMETA(DisplayName = "Consumable"),
	Equipment	UMETA(DisplayName = "Equipment"),
	Material	UMETA(DisplayName = "Material"),
	QuestItem	UMETA(DisplayName = "QuestItem"),
	Placeable	UMETA(DisplayName = "Placeable"),
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> ItemClass;

	FInventoryItem() : ItemID(NAME_None), ItemType(EItemType::Consumable), ItemIcon(nullptr), Quantity(1), ItemClass(nullptr) { }
};
