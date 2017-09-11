// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "../Weapons/BallProjectile.h"
#include "../Weapons/Gun.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.h"
#include "Weapons/Melee.h"



APlayerCharacter::APlayerCharacter()
{
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));

	
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PullTrigger()
{
	if (Melee != nullptr && CurrentEquipState == EEquipState::Armed)
	{
		Melee->OnSwing();
		return;
	}

	if (CurrentEquipState == EEquipState::ShotgunArmed || CurrentEquipState == EEquipState::ShotgunUnarmed)
	{
		Gun->OnFire();
	}
}

bool APlayerCharacter::IsGrabbaleItemInRange()
{
	FVector MyLoc = this->GetActorLocation();
	FVector WeaponLoc = GrabbableMelee->GetActorLocation();
	float result = FVector::Distance(MyLoc, WeaponLoc);
	UE_LOG(LogTemp, Warning, TEXT("%f"), result);
	if (result < GrabRange)
	{
		return true;
	}
	return false;
}

USkeletalMeshComponent* APlayerCharacter::GetMesh1P()
{
	return Mesh1P;
}

AMelee* APlayerCharacter::GetMelee()
{
	return Melee;
}

void APlayerCharacter::SetMelee(AMelee* MeleeToSet)
{
	Melee = MeleeToSet;
}

AMelee* APlayerCharacter::GetGrabbableMelee()
{
	return GrabbableMelee;
}

void APlayerCharacter::SetGrabbableMelee(AMelee* MeleeToGrab)
{
	GrabbableMelee = MeleeToGrab;
}

EEquipState APlayerCharacter::GetEquipState()
{
	return CurrentEquipState;
}

void APlayerCharacter::SetEquipState(EEquipState State)
{
	CurrentEquipState = State;
}

AGun* APlayerCharacter::GetGun()
{
	return Gun;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SheathPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
	}
	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("PullTrigger", IE_Pressed, this, &APlayerCharacter::PullTrigger);
	}
}

