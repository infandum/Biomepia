// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Biomepia_UE4GameMode.h"
#include "Biomepia_UE4Character.h"
#include "UObject/ConstructorHelpers.h"

ABiomepia_UE4GameMode::ABiomepia_UE4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
