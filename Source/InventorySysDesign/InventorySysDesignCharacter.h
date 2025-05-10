// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InventorySysDesignCharacter.generated.h"

UENUM(BlueprintType)
enum class ItemTypes : uint8
{
	Weapon,
	Potion,
	Building,
	Trap,
};

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AInventorySysDesignCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AInventorySysDesignCharacter();
	

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);			

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

//InventorySystemDesign
private :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ItemDrop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ClickAction;

	//ƒ¸ΩΩ∑‘ ≈∞ πŸ¿ŒµÂ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_00;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_02;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_03;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_04;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_05;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_06;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_07;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_08;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_QuickSlot_09;
	//

protected :
	void DropItemAction();
	void InventorySwitching();

	void ClickSwitchAction();

	UFUNCTION()
	void RequestQuickSlotRefresh();

	void SelectQuickSlot(int32 Index);

	int32 CurrentQuickSlotIndex = -1;

	//ƒ¸ΩΩ∑œ ≈∞ º±≈√
	UFUNCTION()	void SelectQuickSlot_00() { SelectQuickSlot(0); }
	UFUNCTION()	void SelectQuickSlot_01() { SelectQuickSlot(1); }
	UFUNCTION()	void SelectQuickSlot_02() { SelectQuickSlot(2); }
	UFUNCTION()	void SelectQuickSlot_03() { SelectQuickSlot(3); }
	UFUNCTION()	void SelectQuickSlot_04() { SelectQuickSlot(4); }
	UFUNCTION()	void SelectQuickSlot_05() { SelectQuickSlot(5); }
	UFUNCTION()	void SelectQuickSlot_06() { SelectQuickSlot(6); }
	UFUNCTION()	void SelectQuickSlot_07() { SelectQuickSlot(7); }
	UFUNCTION()	void SelectQuickSlot_08() { SelectQuickSlot(8); }
	UFUNCTION()	void SelectQuickSlot_09() { SelectQuickSlot(9); }
	//


public :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryComponent;

	//æ∆¿Ã≈€ »πµÊ √≥∏Æ
	void NotifyActorBeginOverlap(AActor* OtherActor);
	
};