// Fill out your copyright notice in the Description page of Project Settings.

#include "Melee.h"


// Sets default values
AMelee::AMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Melee_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Melee_Weapon->bCastDynamicShadow = false;
	Melee_Weapon->CastShadow = false;
	Melee_Weapon->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMelee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMelee::OnSwing()
{
// 	FRotator rotator = Melee_Weapon->GetComponentRotation();
// 	FRotator additionalrotation = FRotator(90, 0, 0);
// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *(rotator.ToString()));
// 	Melee_Weapon->SetWorldRotation(rotator+additionalrotation);
}

