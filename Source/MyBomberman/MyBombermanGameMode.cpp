// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBombermanGameMode.h"
#include "MyBombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyBombermanGameMode::AMyBombermanGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
