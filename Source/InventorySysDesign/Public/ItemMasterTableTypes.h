#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemMasterTableTypes.generated.h"

class AItemBase;

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	Weapon,
	Potion,
	Building,
	Trap,
};

USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemTypes ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSellable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ReferenceID;
};