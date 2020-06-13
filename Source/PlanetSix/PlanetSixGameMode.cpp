// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PlanetSixGameMode.h"
#include "PlanetSixCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlanetSixGameMode::APlanetSixGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//Set seamless travel true by default
	bUseSeamlessTravel = true;
}
