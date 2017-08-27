// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MagicShotgunGameMode.h"
#include "MagicShotgunHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMagicShotgunGameMode::AMagicShotgunGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behavior/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMagicShotgunHUD::StaticClass();
}
