// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Weapons/Melee.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Misc/OutputDeviceDebug.h"
#include "../Weapons/Gun.h"
#include "Kismet/GameplayStatics.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	PlayerCharacter = (APlayerCharacter*)(GetOwner());
}

// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandleComponent"), *GetOwner()->GetName());
	}
}

// Setup (assumed) attached input component
void UGrabber::SetupInputComponent()
{
	/// Look for attached input component (only appears at run time)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Switch", IE_Pressed, this, &UGrabber::Switch);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
	}
}


void UGrabber::Grab()
{
	AMelee* PlayerMelee = PlayerCharacter->GetMelee();

	if (PlayerMelee == nullptr)
	{
		AMelee* MeleeToGrab = PlayerCharacter->GetGrabbableMelee();
		if (MeleeToGrab != nullptr && PlayerCharacter->IsGrabbaleItemInRange())
		{//pickup weapon
			PlayerMelee = MeleeToGrab;
			PlayerMelee->Melee_Weapon->SetSimulatePhysics(false);
			PlayerMelee->AttachToComponent(PlayerCharacter->GetMesh1P(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), TEXT("GripPoint"));
			PlayerCharacter->SetMelee(PlayerMelee);
			PlayerMelee->SetThrownStatus(false);
			PlayerCharacter->SetGrabbableMelee(nullptr);
			PlayerCharacter->SetEquipState(EEquipState::ShotgunArmed);
			Switch();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("no weapon to grab"));
		}
	}
	else if (PlayerCharacter->GetEquipState() == EEquipState::Armed)
	{//throw weapon
		PlayerMelee->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PlayerMelee->Melee_Weapon->SetSimulatePhysics(true);
		PlayerMelee->Melee_Weapon->SetPhysicsLinearVelocity(
			PlayerCharacter->FirstPersonCameraComponent->GetForwardVector() * PlayerMelee->SpeedCoefficient);
		PlayerMelee->SetThrownStatus(true);
		PlayerCharacter->SetMelee(nullptr);
		PlayerCharacter->SetGrabbableMelee(nullptr);
		PlayerCharacter->SetEquipState(EEquipState::Unarmed);
		UGameplayStatics::PlaySound2D(GetWorld(), PlayerCharacter->ThrowSound);
	}


}

void UGrabber::Switch()
{
	AMelee* PlayerMelee = PlayerCharacter->GetMelee();
	USkeletalMeshComponent* PlayerGun = PlayerCharacter->GetGun()->FP_Gun;
	USkeletalMeshComponent* PlayerMesh = PlayerCharacter->GetMesh1P();

	if (PlayerCharacter->GetEquipState() == EEquipState::Unarmed)
	{
		PlayerCharacter->SetEquipState(EEquipState::ShotgunUnarmed);
		PlayerGun->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GunPoint"));
	}
	else if (PlayerCharacter->GetEquipState() == EEquipState::Armed)
	{
		PlayerMelee->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SheathPoint_Gun"));
		PlayerCharacter->SetEquipState(EEquipState::ShotgunArmed);
		PlayerGun->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GunPoint"));
	}
	else if (PlayerCharacter->GetEquipState() == EEquipState::ShotgunUnarmed)
	{
		PlayerCharacter->SetEquipState(EEquipState::Unarmed);
		PlayerGun->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SheathPoint_Melee"));
	}
	else //ShotgunArmed
	{
		PlayerMelee->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		PlayerCharacter->SetEquipState(EEquipState::Armed);
		PlayerGun->AttachToComponent(PlayerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SheathPoint_Melee"));
	}

}


void UGrabber::Launch(AMelee& Melee, FVector Forward)
{

	// 	if (PlayerMelee == nullptr)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("no weapon")); 
	// 		return;
	// 	}
	// 	if (PlayerMelee->ProjectileMovement == nullptr) return;
	// 
	// 	PlayerMelee->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	// 	PlayerMelee->Melee_Weapon->SetSimulatePhysics(true);
	// 	PlayerMelee->ProjectileMovement->Activate();
	// 	PlayerMelee->ProjectileMovement->UpdatedComponent = PlayerMelee->Melee_Weapon;
	// 	PlayerMelee->ProjectileMovement->bRotationFollowsVelocity = true;
	// 	PlayerMelee->ProjectileMovement->bShouldBounce = true;
	// 	PlayerMelee->ProjectileMovement->SetVelocityInLocalSpace(
	// 		PlayerCharacter->FirstPersonCameraComponent->GetForwardVector() * PlayerMelee->SpeedCoefficient * 100);
	// 	PlayerMelee->OnThrow();
	// 	PlayerMelee->Melee_Weapon->SetPhysicsLinearVelocity(
	//  		PlayerCharacter->FirstPersonCameraComponent->GetForwardVector() * PlayerMelee->SpeedCoefficient);
	// 	PlayerCharacter->SetMelee(nullptr);

	//throw
	// 		PlayerMelee->SetThrownStatus(true);
	// 		FOutputDeviceDebug debug;
	// 		PlayerMelee->CallFunctionByNameWithArguments(TEXT("PlayThrow"), debug, NULL, true);
	//		PlayerMelee->ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	// 		if (PlayerMelee->ProjectileMovement != nullptr)
	// 		{
	// 			//PlayerMelee->ProjectileMovement->Activate();
	// 			PlayerMelee->ProjectileMovement->UpdatedComponent = PlayerMelee->Melee_Weapon;
	// 			PlayerMelee->ProjectileMovement->InitialSpeed = 3000.f;
	// 			PlayerMelee->ProjectileMovement->MaxSpeed = 3000.f;
	// 			PlayerMelee->ProjectileMovement->bRotationFollowsVelocity = true;
	// 			PlayerMelee->ProjectileMovement->bShouldBounce = true;
	// 		}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UGrabber::GetFirstPhysicsBodyInReach(FHitResult& outHitResult)
{
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		outHitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(GrabRadius)
	);
	FColor ResultColor = bHasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), outHitResult.Location, 0, GrabRadius, FQuat::Identity, ResultColor, true, 100);
	return bHasHit;
}

// Return current start of reach line
FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * GrabRange * 0.5);
}

// Return current end of reach line
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * GrabRange);
}
