// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UQuickSlotSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UQuickSlotSlotWidget::SetItemData(UTexture2D *Icon, int32 Count)
{
	UE_LOG(LogTemp, Log, TEXT("[UI] SetItemData called. Icon: %s | Count: %d"),Icon ? *Icon->GetName() : TEXT("None"), Count);

	if(ItemImage && Icon)	ItemImage->SetBrushFromTexture(Icon);
	if(QuantityText)				QuantityText->SetText(FText::AsNumber(Count));
}