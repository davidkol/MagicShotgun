// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors()
{

	auto rando = FMath::RandPointInBox(FBox(FVector(0, -1900.0f, -100.0f), FVector(3950.0f, 1900.0f, 0.0f)));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *rando.ToString());
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

