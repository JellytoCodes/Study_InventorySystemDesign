// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInventorySlotWidget::SetItemData(UTexture2D *Icon, int32 Quantity)
{
	if(ItemImage && Icon)	ItemImage->SetBrushFromTexture(Icon);
	else if(ItemImage)		ItemImage->SetBrushFromTexture(nullptr);

	if(QuantityText)
	{
		QuantityText->SetText(FText::AsNumber(Quantity));
		QuantityText->SetVisibility(Quantity >= 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
