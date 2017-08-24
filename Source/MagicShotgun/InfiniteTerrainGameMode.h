// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicShotgunGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;

/**
 * 
 */
UCLASS()
class MAGICSHOTGUN_API AInfiniteTerrainGameMode : public AMagicShotgunGameMode
{
	GENERATED_BODY()
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bounds Pool")
	UActorPool* NavMeshBoundsVolumePool;

private:

	void AddToPool(ANavMeshBoundsVolume* BoundsVolumeToAdd);

};
