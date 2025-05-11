// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "InventoryComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ItemID: %s, Quantity: %d"), *ItemData.ItemID.ToString(), ItemData.Quantity);
}

void AItemBase::OnPickedUp(AActor *Picker)
{
	if(UInventoryComponent* Inventory = Picker->FindComponentByClass<UInventoryComponent>())
	{
		Inventory->AddItem(ItemData);

		UE_LOG(LogTemp, Log, TEXT("[Root] Item : %s | Quantity : %d"), *ItemData.ItemID.ToString(), ItemData.Quantity);
		Destroy();
	}
}

void AItemBase::SetItemData(const FInventoryItem &NewItemData)
{
	ItemData = NewItemData;
}
