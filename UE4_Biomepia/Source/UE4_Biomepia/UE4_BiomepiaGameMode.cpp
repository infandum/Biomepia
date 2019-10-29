// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4_BiomepiaGameMode.h"
#include "UE4_BiomepiaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4_BiomepiaGameMode::AUE4_BiomepiaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
