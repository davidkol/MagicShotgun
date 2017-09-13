// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Mannequin.h"
#include "PlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UGrabber;
class AMelee;
class AGun;

UENUM()
enum class EEquipState : uint8
{
	Unarmed,
	Armed,
	ShotgunUnarmed,
	ShotgunArmed
};
/**
 * 
 */
UCLASS()
class MAGICSHOTGUN_API APlayerCharacter : public AMannequin
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Grab")
	bool IsGrabbaleItemInRange();

	USkeletalMeshComponent* GetMesh1P();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AMelee* GetMelee();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetMelee(AMelee* MeleeToSet);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AMelee* GetGrabbableMelee();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetGrabbableMelee(AMelee* MeleeToGrab);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	EEquipState GetEquipState();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetEquipState(EEquipState State);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AGun* GetGun();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AdjustCharge(float DeltaTime, float CurveCoefficient);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float GetCharge();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

protected:
	virtual void BeginPlay() override;

private:
	AMelee* Melee;

	AMelee* GrabbableMelee;
	
	AGun* Gun;

	EEquipState CurrentEquipState = EEquipState::Unarmed;

	UPROPERTY(VisibleDefaultsOnly, Category = "Setup")
	UGrabber* Grabber;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float GrabRange = 500.f;

	float Charge = 0.f;
};
