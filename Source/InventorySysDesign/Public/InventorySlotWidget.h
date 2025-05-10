// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class UTextBlock;
struct FInventoryItem;

UCLASS()
class INVENTORYSYSDESIGN_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	//Slot에 Icon과 수량 정보 입력
	void SetItemData(const FInventoryItem& InItem);
	
	void OnMouseEnterSlot();
	void OnMouseLeaveSlot();

protected :
	virtual void NativeConstruct() override;	

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	class ACharacterHUD* OwningHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FInventoryItem ItemData;
};
