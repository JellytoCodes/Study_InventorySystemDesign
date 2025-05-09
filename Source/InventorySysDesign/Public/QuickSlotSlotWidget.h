// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotSlotWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class INVENTORYSYSDESIGN_API UQuickSlotSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :	
	//Slot�� Icon�� ���� ���� �Է�
	void SetItemData(UTexture2D* Icon, int32 Count);

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

};
