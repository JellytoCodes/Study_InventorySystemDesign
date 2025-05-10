// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventorySysDesignCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "CharacterHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AInventorySysDesignCharacter

AInventorySysDesignCharacter::AInventorySysDesignCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AInventorySysDesignCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if(InventoryComponent)
	{
		InventoryComponent->OnInventoryUpdated.AddDynamic(this, &AInventorySysDesignCharacter::RequestQuickSlotRefresh);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInventorySysDesignCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInventorySysDesignCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInventorySysDesignCharacter::Look);


		//InventorySystem Key
		EnhancedInputComponent->BindAction(IA_ItemDrop, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::DropItemAction);
		EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::InventorySwitching);

		EnhancedInputComponent->BindAction(IA_ClickAction, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::ClickSwitchAction);

		//QuickSlot Key
		EnhancedInputComponent->BindAction(IA_QuickSlot_00, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_00);
		EnhancedInputComponent->BindAction(IA_QuickSlot_01, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_01);
		EnhancedInputComponent->BindAction(IA_QuickSlot_02, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_02);
		EnhancedInputComponent->BindAction(IA_QuickSlot_03, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_03);
		EnhancedInputComponent->BindAction(IA_QuickSlot_04, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_04);
		EnhancedInputComponent->BindAction(IA_QuickSlot_05, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_05);
		EnhancedInputComponent->BindAction(IA_QuickSlot_06, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_06);
		EnhancedInputComponent->BindAction(IA_QuickSlot_07, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_07);
		EnhancedInputComponent->BindAction(IA_QuickSlot_08, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_08);
		EnhancedInputComponent->BindAction(IA_QuickSlot_09, ETriggerEvent::Started, this, &AInventorySysDesignCharacter::SelectQuickSlot_09);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AInventorySysDesignCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AInventorySysDesignCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//InventorySystemDesign
void AInventorySysDesignCharacter::NotifyActorBeginOverlap(AActor *OtherActor)
{
	if(AItemBase* Item = Cast<AItemBase>(OtherActor))
	{
		Item->OnPickedUp(this);
	}
}

void AInventorySysDesignCharacter::DropItemAction()
{
	if(CurrentQuickSlotIndex < 0 || CurrentQuickSlotIndex > 9) return;

	TArray<FInventoryItem> QuickItems;
	InventoryComponent->GetQuickSlotItems(QuickItems);

	if(QuickItems.IsValidIndex(CurrentQuickSlotIndex))
	{
		const FInventoryItem& SelectedItem = QuickItems[CurrentQuickSlotIndex];
		InventoryComponent->DropItem(SelectedItem.ItemID, 1);
	}
}

void AInventorySysDesignCharacter::InventorySwitching()
{
	if(ACharacterHUD* HUD = Cast<ACharacterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		TArray<FInventoryItem> AllItems;
		InventoryComponent->GetAllItems(AllItems);

		//인벤토리 아이템 정렬
		InventoryComponent->SortItems(AllItems, EInventorySortType::Quantity);

		HUD->ToggleInventory(AllItems);
	}
}

void AInventorySysDesignCharacter::ClickSwitchAction()
{
	//아이템 타입 결정
	ItemTypes ItemType = ItemTypes::Weapon;
	//
	switch(ItemType)
	{
		case ItemTypes::Weapon :
			//AttackAction();
		break;

		case ItemTypes::Potion :
			//InteractAction();
		break;

		case ItemTypes::Building :
			//BuildAction();
		break;

		case ItemTypes::Trap :
			//BuildAction();
		break;
	}
}

void AInventorySysDesignCharacter::RequestQuickSlotRefresh()
{
	if(ACharacterHUD* HUD = Cast<ACharacterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		TArray<FInventoryItem> QuickItems;
		InventoryComponent->GetQuickSlotItems(QuickItems);

		HUD->ShowQuickSlot(QuickItems);
		UE_LOG(LogTemp, Log, TEXT("RequestQuickSlotRefresh Called"));
	}
}

void AInventorySysDesignCharacter::SelectQuickSlot(int32 Index)
{
	if( Index < 0 || Index > 9) return;

	CurrentQuickSlotIndex = Index;
	UE_LOG(LogTemp, Log, TEXT("Selected Quick Slot : %d"), Index);

	if(ACharacterHUD* HUD = Cast<ACharacterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		HUD->HighlightQuickSlot(Index);
	}
}
