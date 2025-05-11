// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

//�κ��丮 ����
UENUM(BlueprintType)
enum class EInventorySortType : uint8
{
    Name,
    Quantity,
    ItemType,
    Price,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSDESIGN_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

    TMap<FName, FInventoryItem> InventoryMap;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
    
    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated OnInventoryUpdated;
    
	// ������ �߰�
    UFUNCTION(BlueprintCallable)
    bool AddItem(const FInventoryItem& NewItem);

    // ������ ����
    UFUNCTION(BlueprintCallable)
    bool RemoveItem(FName ItemID, int32 Count = 1);
    
    //������ ��� ó��
	void DropItem(const FInventoryItem& Item);

    // �ش� ������ ���� ��ȯ 
    UFUNCTION(BlueprintCallable)
    int32 GetItemQuantity(FName ItemID) const;

    // UI�� �迭 ���·� ��ȯ
    UFUNCTION(BlueprintCallable)
    TArray<FInventoryItem> GetInventoryAsArray() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void GetQuickSlotItems(TArray<FInventoryItem>& OutQuickSlotItems) const;

    void GetAllItems(TArray<FInventoryItem>& OutItems) const;
    
    //�κ��丮 ���� ����
    void SortItems(TArray<FInventoryItem>& Items, EInventorySortType SortType) const;
};
