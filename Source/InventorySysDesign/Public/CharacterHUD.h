// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryItem.h"
#include "ItemDBSubsystem.h"
#include "CharacterHUD.generated.h"

class UQuickSlotWidget;
class UInventoryWidget;
class UInventoryToolTipWidget;
struct FInventoryItem;

UCLASS()
class INVENTORYSYSDESIGN_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public :
	ACharacterHUD();
	virtual void BeginPlay() override;

	void ShowQuickSlot(const TArray<FInventoryItem>& Items);
	
	void ToggleInventory(const TArray<FInventoryItem> &Items);

	void HighlightQuickSlot(int32 Index);

	void ShowItemToolTip(const FInventoryItem& Item);
	void ShowItemToolTip(const FItemDataRow* Item);
	void HideItemToolTip();

private :
	UPROPERTY()
	UQuickSlotWidget* QuickSlotWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "QuickSlot")
	TSubclassOf<UQuickSlotWidget> QuickSlotWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryToolTipWidget* ToolTipWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "ToolTip")
	TSubclassOf<UInventoryToolTipWidget> ToolTipWidgetClass;

	bool bIsInventoryOpen = false;
};