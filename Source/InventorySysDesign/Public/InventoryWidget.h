// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UInventorySlotWidget;

UCLASS()
class INVENTORYSYSDESIGN_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void RefreshInventory(const TArray<FInventoryItem>& Items);

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* SortComboBox;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UInventorySlotWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 NumColumns = 5;

	UFUNCTION()
	void OnSortOptionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	TArray<FInventoryItem> CachedItems;

	UPROPERTY()
	class UInventoryComponent* InventoryComponent;
};
