// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "QuickSlotSlotWidget.generated.h"

class UImage;
class UTextBlock;
class UBorder;

UCLASS()
class INVENTORYSYSDESIGN_API UQuickSlotSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :	
	//Slot에 Icon과 수량 정보 입력
	void SetItemData(const FInventoryItem& Item);

	UFUNCTION(BlueprintCallable)
	void SetHighlight(bool bSelected);

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(meta = (BindWidget))
	UBorder* HighlightBorder;

};
