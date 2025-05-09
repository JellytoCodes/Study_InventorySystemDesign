// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "QuickSlotWidget.generated.h"

class UHorizontalBox;
class UQuickSlotSlotWidget;
struct FInventoryItem;

UCLASS()
class INVENTORYSYSDESIGN_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void RefreshQuickSlots(const TArray<FInventoryItem>& QuickSlotItems);

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* QuickSlotBox;

	UPROPERTY(EditAnywhere, Category = "QuickSlot")
	TSubclassOf<UQuickSlotSlotWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, Category = "QuickSlot")
	int32 MaxSlotCount = 10;

private :
	//퀵슬롯에 순차적으로 SlotSlotWidget 생성
	void CreateInitialSlots();
};
