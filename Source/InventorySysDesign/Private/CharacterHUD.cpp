#include "CharacterHUD.h"
#include "QuickSlotWidget.h"
#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "InventoryToolTipWidget.h"

ACharacterHUD::ACharacterHUD()
{
	static ConstructorHelpers::FClassFinder<UQuickSlotWidget> QuickSlotWidgetBP(TEXT("/Game/WidgetBP/WBP_QuickSlotWidget.WBP_QuickSlotWidget_C"));
	if(QuickSlotWidgetBP.Succeeded())
	{
		QuickSlotWidgetClass = QuickSlotWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UInventoryWidget> InventoryWidgetBP(TEXT("/Game/WidgetBP/WBP_InventoryWidget.WBP_InventoryWidget_C"));
	if(InventoryWidgetBP.Succeeded())
	{
		InventoryWidgetClass = InventoryWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UInventoryToolTipWidget> ToolTipWidgetBP(TEXT("/Game/WidgetBP/WBP_InventoryToolTipWidget.WBP_InventoryToolTipWidget_C"));
	if(ToolTipWidgetBP.Succeeded())
	{
		 ToolTipWidgetClass = ToolTipWidgetBP.Class;
	}

}

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();

	//狞浇吩 UI 积己
	if(QuickSlotWidgetClass)
	{
		QuickSlotWidgetInstance = CreateWidget<UQuickSlotWidget>(GetWorld(), QuickSlotWidgetClass);
		if(QuickSlotWidgetInstance)
		{
			UE_LOG(LogTemp, Log, TEXT("AddToViewport"));
			QuickSlotWidgetInstance->AddToViewport();
		}
	}

	//牢亥配府 UI 积己
	if(InventoryWidgetClass)
	{
		InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	}
}

void ACharacterHUD::ShowQuickSlot(const TArray<FInventoryItem> &Items)
{
	if(QuickSlotWidgetInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("ShowQuickSlot"));
		QuickSlotWidgetInstance->RefreshQuickSlots(Items);
	}
}

void ACharacterHUD::ToggleInventory(const TArray<FInventoryItem> &Items)
{
	if(!bIsInventoryOpen)
	{
		InventoryWidgetInstance->RefreshInventory(Items);
		InventoryWidgetInstance->AddToViewport();
		bIsInventoryOpen = !bIsInventoryOpen;
	}
	else
	{
		InventoryWidgetInstance->RemoveFromParent();
		bIsInventoryOpen = !bIsInventoryOpen;
	}
}

void ACharacterHUD::HighlightQuickSlot(int32 Index)
{
	if(QuickSlotWidgetInstance)
	{
		QuickSlotWidgetInstance->HighlightSlot(Index);
	}
}

void ACharacterHUD::ShowItemToolTip(const FInventoryItem &Item)
{
	UE_LOG(LogTemp, Log, TEXT("ShowItemToolTip"));
	if(!ToolTipWidgetInstance && ToolTipWidgetClass)
	{
		ToolTipWidgetInstance = CreateWidget<UInventoryToolTipWidget>(GetWorld(), ToolTipWidgetClass);
	}

	if(ToolTipWidgetInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("Show %s Item ToolTip"), *Item.ItemID.ToString());
		ToolTipWidgetInstance->AddToViewport(100);
		ToolTipWidgetInstance->Setup(Item);
	}
}

void ACharacterHUD::HideItemToolTip()
{
	UE_LOG(LogTemp, Log, TEXT("HideItemToolTip"));
	if(ToolTipWidgetInstance)
	{
		ToolTipWidgetInstance->RemoveFromParent();
		UE_LOG(LogTemp, Log, TEXT("Hide ToolTip"));
	}
}
