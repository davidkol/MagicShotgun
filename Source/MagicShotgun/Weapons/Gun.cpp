// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "../Weapons/BallProjectile.h"
#include "Animation/AnimInstance.h"

// Sets default values
AGun::AGun()
{

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	//FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			for (int32 i = 0; i < ShotCount; i++)
			{
				FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
				float pitch = FMath::FRandRange(SpawnRotation.Pitch - RotationRange, SpawnRotation.Pitch + RotationRange);
				float yaw = FMath::FRandRange(SpawnRotation.Yaw - RotationRange, SpawnRotation.Yaw + RotationRange);
				float roll = FMath::FRandRange(SpawnRotation.Roll - RotationRange, SpawnRotation.Roll + RotationRange);
				SpawnRotation = FRotator(pitch, yaw, roll);

				//const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}


	// try and play a firing animation if specified
// 	if (FireAnimation1P != NULL && AnimInstance1P != NULL)
// 	{
// 		AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);
// 	}
// 
// 	if (FireAnimation3P != NULL && AnimInstance3P != NULL)
// 	{
// 		AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
// 	}
}

bool AGun::dick()
{
	return false;
}

