// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "QuickSlotSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "InventoryComponent.h"

UQuickSlotWidget::UQuickSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultIconTexture(TEXT("/Game/Blueprints/DefaultIcon.DefaultIcon"));
	if(DefaultIconTexture.Succeeded())
	{
		DefaultIcon = DefaultIconTexture.Object;
	}
}

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

void UQuickSlotWidget::RefreshQuickSlots(const TArray<FInventoryItem>& QuickSlotItems)
{
    if (!QuickSlotBox) return;

	UE_LOG(LogTemp, Log, TEXT("Called RefreshQuickSlots"));
    const TArray<UWidget*>& Slots = QuickSlotBox->GetAllChildren();

    for(int32 i = 0; i < Slots.Num(); i++)
    {
        if(UQuickSlotSlotWidget* SlotWidget = Cast<UQuickSlotSlotWidget>(Slots[i]))
        {
            if(QuickSlotItems.IsValidIndex(i) && QuickSlotItems[i].Quantity > 0)
            {
                SlotWidget->SetItemData(QuickSlotItems[i]);
            }
            else
            {
				FInventoryItem DummyItem;
				DummyItem.ItemID = NAME_None;
				DummyItem.Quantity = 0;

                SlotWidget->SetItemData(DummyItem);
            }
        }
    }
}

void UQuickSlotWidget::HighlightSlot(int32 Index)
{
	const TArray<UWidget*>& Slots = QuickSlotBox->GetAllChildren();

	for(int32 i = 0 ; i < Slots.Num() ; i++)
	{
		if(UQuickSlotSlotWidget* SlotWidget = Cast<UQuickSlotSlotWidget>(Slots[i]))
		{
			SlotWidget->SetHighlight(i == Index);
		}
	}
}
