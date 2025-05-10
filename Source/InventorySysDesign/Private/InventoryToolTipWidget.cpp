// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryToolTipWidget.h"
#include "Components/TextBlock.h"

void UInventoryToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryToolTipWidget::Setup(const FInventoryItem &Item)
{
	if(Item.ItemID == NAME_None) return;

	if(ItemNameText)
	{
		ItemNameText->SetText(FText::FromName(Item.ItemID));
	}
	if(ItemDescText)
	{
		ItemDescText->SetText(FText::FromString(Item.ItemDesc));
	}

	FVector2D MousePos;
	if(GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
	{
		SetPositionInViewport(MousePos + FVector2D(15.f, 15.f), true);
	}
}