// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;
class UInputComponent;
class AMelee;
class APlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICSHOTGUN_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//AActor * Owner;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Grab")
	float GrabRange = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Grab")
	float GrabRadius = 500.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	APlayerCharacter* PlayerCharacter;

	// Ray-cast and grab whats in reach
	void Grab();

	// Call when grab is released
	void Switch();

	void Launch(AMelee& Melee, FVector Forward);

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	bool GetFirstPhysicsBodyInReach(FHitResult& outHitResult);

	// Returns current start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
};
