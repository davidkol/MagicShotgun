// Fill out your copyright notice in the Description page of Project Settings.

#include "Melee.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AMelee::AMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Melee_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = Melee_Weapon;
	Melee_Weapon->bCastDynamicShadow = false;
	Melee_Weapon->CastShadow = false;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

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
	
}

void AMelee::OnThrow()
{
	// Use a ProjectileMovementComponent to govern this projectile's movement
// 	if (ProjectileMovement == nullptr) return;
// 	ProjectileMovement->UpdatedComponent = Melee_Weapon;
// 	ProjectileMovement->InitialSpeed = 3000.f;
// 	ProjectileMovement->MaxSpeed = 3000.f;
// 	ProjectileMovement->bRotationFollowsVelocity = true;
// 	ProjectileMovement->bShouldBounce = true;
}

