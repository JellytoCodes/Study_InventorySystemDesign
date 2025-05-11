// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "ItemDBSubsystem.h"

void UQuickSlotSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UQuickSlotSlotWidget::SetItemData(const FInventoryItem& Item)
{
    if (Item.ItemID == NAME_None || Item.Quantity <= 0)
    {
        // 비어 있는 슬롯 처리
        ItemImage->SetBrushFromTexture(nullptr);
        QuantityText->SetText(FText::GetEmpty());
        return;
    }

    UItemDBSubsystem* ItemDB = GetGameInstance()->GetSubsystem<UItemDBSubsystem>();
    if (!ItemDB) return;

    const FItemDataRow* ItemData = ItemDB->GetItemData(Item.ItemID);
    if (!ItemData) return;

    if (ItemData->ItemIcon)
    {
        ItemImage->SetBrushFromTexture(ItemData->ItemIcon);
    }

    QuantityText->SetText(FText::AsNumber(Item.Quantity));
    QuantityText->SetVisibility(Item.Quantity > 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UQuickSlotSlotWidget::SetHighlight(bool bSelected)
{
	if(HighlightBorder)
	{
		HighlightBorder->SetBrushColor(bSelected ? FLinearColor::Yellow : FLinearColor::Transparent);
	}
}
