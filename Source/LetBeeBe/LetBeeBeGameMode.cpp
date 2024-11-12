// Copyright Epic Games, Inc. All Rights Reserved.

#include "LetBeeBeGameMode.h"
#include "LetBeeBeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerHUD.h"

ALetBeeBeGameMode::ALetBeeBeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	HUDClass = APlayerHUD::StaticClass();
}
