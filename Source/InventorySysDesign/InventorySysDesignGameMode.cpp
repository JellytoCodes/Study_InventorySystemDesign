// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventorySysDesignGameMode.h"
#include "InventorySysDesignCharacter.h"
#include "Public/CharacterHUD.h"
#include "UObject/ConstructorHelpers.h"

AInventorySysDesignGameMode::AInventorySysDesignGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	HUDClass = ACharacterHUD::StaticClass();
}
