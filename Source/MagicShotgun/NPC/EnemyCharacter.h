// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Mannequin.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MAGICSHOTGUN_API AEnemyCharacter : public AMannequin
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();
	
	
};
