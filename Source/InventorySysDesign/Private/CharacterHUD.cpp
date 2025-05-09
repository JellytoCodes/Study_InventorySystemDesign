#include "CharacterHUD.h"
#include "QuickSlotWidget.h"
#include "InventoryWidget.h"
#include "InventoryComponent.h"

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

}

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();

	if(QuickSlotWidgetClass)
	{
		QuickSlotWidgetInstance = CreateWidget<UQuickSlotWidget>(GetWorld(), QuickSlotWidgetClass);
		if(QuickSlotWidgetInstance)
		{
			UE_LOG(LogTemp, Log, TEXT("AddToViewport"));
			QuickSlotWidgetInstance->AddToViewport();
		}
	}
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