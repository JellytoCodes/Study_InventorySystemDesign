// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "InventorySlotWidget.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::RefreshInventory(const TArray<FInventoryItem> &Items)
{
	if(!InventoryGrid || !SlotWidgetClass) return;

	InventoryGrid->ClearChildren();

	for(int32 i = 0 ; i < Items.Num() ; i++)
	{
		UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
		if(SlotWidget)
		{
			SlotWidget->SetItemData(Items[i].ItemIcon, Items[i].Quantity);

			UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(SlotWidget);
			if(GridSlot)
			{
				GridSlot->SetColumn(i % NumColumns);
				GridSlot->SetRow(i / NumColumns);
			}
		}

	}
}
