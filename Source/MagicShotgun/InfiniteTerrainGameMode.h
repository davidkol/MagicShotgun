// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicShotgunGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;

/**
 * 
 */
UCLASS()
class MAGICSHOTGUN_API AInfiniteTerrainGameMode : public AMagicShotgunGameMode
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void PopulateBoundsVolumePool();
	
private:

	void AddToPool(ANavMeshBoundsVolume* BoundsVolumeToAdd);
};
