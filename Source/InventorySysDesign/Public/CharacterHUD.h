// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryItem.h"
#include "CharacterHUD.generated.h"

class UQuickSlotWidget;
class UInventoryWidget;

UCLASS()
class INVENTORYSYSDESIGN_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public :
	ACharacterHUD();
	virtual void BeginPlay() override;

	void ShowQuickSlot(const TArray<FInventoryItem>& Items);

	void ToggleInventory(const TArray<FInventoryItem> &Items);

private :
	UPROPERTY()
	UQuickSlotWidget* QuickSlotWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuickSlotWidget> QuickSlotWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	bool bIsInventoryOpen = false;
};