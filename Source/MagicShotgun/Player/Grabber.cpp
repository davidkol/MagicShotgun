// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Weapons/Melee.h"
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
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
	}
}


void UGrabber::Grab()
{
	FHitResult HitResult; 
	auto PlayerCharacter = (APlayerCharacter*)(GetOwner());
	/// If we hit something, then attach a physics handle
	if (GetFirstPhysicsBodyInReach(HitResult))
	{
		PlayerCharacter->Melee = (AMelee*)(HitResult.GetActor());
		PlayerCharacter->Melee->AttachToComponent(PlayerCharacter->GetMesh1P(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
// 		if (!PhysicsHandle) { return; }
// 		PhysicsHandle->GrabComponent(
// 			ComponentToGrab,
// 			NAME_None, // no bones needed
// 			ComponentToGrab->GetOwner()->GetActorLocation(),
// 			true // allow rotation
// 		);
	}
}

void UGrabber::Release()
{
// 	if (!PhysicsHandle) { return; }
// 	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// 	if (!PhysicsHandle) { return; }
// 	// if the physics handle is attached
// 	if (PhysicsHandle->GrabbedComponent)
// 	{
// 		// move the object that we're holding
// 		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
// 	}

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
