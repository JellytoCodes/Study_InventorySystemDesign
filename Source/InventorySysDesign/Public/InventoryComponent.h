// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSDESIGN_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated OnInventoryUpdated;

	/** 아이템 추가 */
    UFUNCTION(BlueprintCallable)
    bool AddItem(const FInventoryItem& NewItem);

    /** 아이템 제거 */
    UFUNCTION(BlueprintCallable)
    bool RemoveItem(FName ItemID, int32 Count = 1);

    /** 해당 아이템 수량 반환 */
    UFUNCTION(BlueprintCallable)
    int32 GetItemQuantity(FName ItemID) const;

    /** UI용 배열 형태로 반환 */
    UFUNCTION(BlueprintCallable)
    TArray<FInventoryItem> GetInventoryAsArray() const;
  
	//아이템 드랍 처리
	void DropItem(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GetQuickSlotItems(TArray<FInventoryItem>& OutQuickSlotItems) const;

    void GetAllItems(TArray<FInventoryItem>& OutItems) const;
protected:
    UPROPERTY(VisibleAnywhere)
    TMap<FName, FInventoryItem> InventoryMap;

};
