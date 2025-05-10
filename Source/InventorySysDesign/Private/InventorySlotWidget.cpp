// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CharacterHUD.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
	    OwningHUD = Cast<ACharacterHUD>(PC->GetHUD());
	}
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	OnMouseEnterSlot();
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	OnMouseLeaveSlot();
}

void UInventorySlotWidget::SetItemData(const FInventoryItem& InItem)
{
	ItemData = InItem;
	if(ItemImage && InItem.ItemIcon)	ItemImage->SetBrushFromTexture(InItem.ItemIcon);
	else if(ItemImage)					ItemImage->SetBrushFromTexture(nullptr);

	if(QuantityText)
	{
		QuantityText->SetText(FText::AsNumber(InItem.Quantity));
		QuantityText->SetVisibility(InItem.Quantity >= 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UInventorySlotWidget::OnMouseEnterSlot()
{
	if(OwningHUD)
	{
		UE_LOG(LogTemp, Log, TEXT("MosuerEnter"));
		OwningHUD->ShowItemToolTip(ItemData);
	}
}

void UInventorySlotWidget::OnMouseLeaveSlot()
{
	if(OwningHUD)
	{
		UE_LOG(LogTemp, Log, TEXT("MosuerLeave"));
		OwningHUD->HideItemToolTip();
	}
}