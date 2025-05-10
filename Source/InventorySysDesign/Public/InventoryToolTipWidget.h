// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventoryToolTipWidget.generated.h"

class UTextBlock;
struct FInventoryItem;

UCLASS()
class INVENTORYSYSDESIGN_API UInventoryToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable)
	void Setup(const FInventoryItem& Item);

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescText;
};
