// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "InventorySlotWidget.h"
#include "CharacterHUD.h"
#include "InventoryComponent.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(SortComboBox)
	{
		SortComboBox->ClearOptions();
		SortComboBox->AddOption(TEXT("Name"));
		SortComboBox->AddOption(TEXT("Quantity"));
		SortComboBox->AddOption(TEXT("ItemType"));
		SortComboBox->AddOption(TEXT("Price"));
		SortComboBox->SetSelectedIndex(0);

		SortComboBox->OnSelectionChanged.AddDynamic(this, &UInventoryWidget::OnSortOptionChanged);
	}

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(PlayerChar)
	{
		InventoryComponent = PlayerChar->FindComponentByClass<UInventoryComponent>();
	}
}

void UInventoryWidget::RefreshInventory(const TArray<FInventoryItem> &Items)
{
	if(!InventoryGrid || !SlotWidgetClass) return;

	CachedItems = Items;

	InventoryGrid->ClearChildren();

	for(int32 i = 0 ; i < Items.Num() ; i++)
	{
		UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
		if(SlotWidget)
		{
			SlotWidget->SetItemData(Items[i]);

			UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(SlotWidget);
			if(GridSlot)
			{
				GridSlot->SetColumn(i % NumColumns);
				GridSlot->SetRow(i / NumColumns);
			}
		}
	}
}

void UInventoryWidget::OnSortOptionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	EInventorySortType SortType = EInventorySortType::Name;

	if(SelectedItem == TEXT("Quantity")) SortType = EInventorySortType::Quantity;
	else if(SelectedItem == TEXT("ItemType")) SortType = EInventorySortType::ItemType;
	else if(SelectedItem == TEXT("Price")) SortType = EInventorySortType::Price;

	TArray<FInventoryItem> SortedItems = CachedItems;
	if(InventoryComponent)
	{
		InventoryComponent->SortItems(SortedItems, SortType);
		RefreshInventory(SortedItems);
	}
}