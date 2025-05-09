// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "QuickSlotSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateInitialSlots();
}

void UQuickSlotWidget::CreateInitialSlots()
{
	if(!SlotWidgetClass || !QuickSlotBox) return;

	QuickSlotBox->ClearChildren();

	for(int32 i = 0 ; i < MaxSlotCount ; i++)
	{
		UQuickSlotSlotWidget* NewSlot = CreateWidget<UQuickSlotSlotWidget>(this, SlotWidgetClass);
		if(NewSlot)
		{
			UHorizontalBoxSlot* BoxSlot = QuickSlotBox->AddChildToHorizontalBox(NewSlot);
			if(BoxSlot)
			{
				// 패딩 설정
				BoxSlot->SetPadding(FMargin(4.0f, 0.0f));

				// 사이즈 고정
				BoxSlot->SetSize(ESlateSizeRule::Automatic);
				NewSlot->SetDesiredSizeInViewport(FVector2D(120.f, 120.f)); // 보조 설정

				// 정렬도 명시
				BoxSlot->SetHorizontalAlignment(HAlign_Center);
				BoxSlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
}

void UQuickSlotWidget::RefreshQuickSlots(const TArray<FInventoryItem> &QuickSlotItems)
{
	if(!QuickSlotBox) return;

	int32 Index = 0;
	for(UWidget* Child : QuickSlotBox->GetAllChildren())
	{
		if(UQuickSlotSlotWidget* SlotWidget = Cast<UQuickSlotSlotWidget>(Child))
		{
			UE_LOG(LogTemp, Log, TEXT("Cast<UQuickSlotSlotWidget>(Child)"));
			if(QuickSlotItems.IsValidIndex(Index))
			{
				UE_LOG(LogTemp, Log, TEXT("QuickSLotItems.IsValidIndex"));
				const FInventoryItem& Item = QuickSlotItems[Index];
				SlotWidget->SetItemData(Item.ItemIcon, Item.Quantity);
			}
			else
			{
				SlotWidget->SetItemData(nullptr, 0);
			}
		}
		Index++;
	}
}