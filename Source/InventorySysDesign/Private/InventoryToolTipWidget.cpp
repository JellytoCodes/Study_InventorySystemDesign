// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryToolTipWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UInventoryToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryToolTipWidget::Setup(const FInventoryItem &Item)
{
	UItemDBSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemDBSubsystem>();
	if(!ItemDB) return;

	const FItemDataRow* ItemData = ItemDB->GetItemData(Item.ItemID);
	if(!ItemData) return;

	if(ItemNameText)
	{
		ItemNameText->SetText(ItemData->DisplayName);
	}
	if(ItemDescText)
	{
		ItemDescText->SetText(ItemData->Description);
	}

	FVector2D MousePos;
	if(GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
	{
		SetPositionInViewport(MousePos + FVector2D(15.f, 15.f), true);
	}
}

void UInventoryToolTipWidget::Setup(const FItemDataRow *Item)
{
	if(!Item) return;

	if(ItemNameText)
	{
		ItemNameText->SetText(Item->DisplayName);
	}

	if(ItemDescText)
	{
		ItemDescText->SetText(Item->Description);
	}

	FVector2D MousePos;
	if(GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
	{
		SetPositionInViewport(MousePos + FVector2D(15.f, 15.f), true);
	}
}
