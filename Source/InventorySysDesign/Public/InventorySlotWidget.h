// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class INVENTORYSYSDESIGN_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	//Slot에 Icon과 수량 정보 입력
	void SetItemData(UTexture2D* Icon, int32 Quantity);

protected :
	virtual void NativeConstruct() override;	

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

};
