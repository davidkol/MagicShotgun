// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MagicShotgunGameMode.h"
#include "MagicShotgunHUD.h"
#include "UObject/ConstructorHelpers.h"

AMagicShotgunGameMode::AMagicShotgunGameMode()
	: Super()
{
	// use our custom HUD class
	HUDClass = AMagicShotgunHUD::StaticClass();
}
