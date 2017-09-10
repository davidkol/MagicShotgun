// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Mannequin.h"
#include "PlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UGrabber;
class AMelee;
class AGun;

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
	bool IsMeleeEquipped();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetIsMeleeEquipped(bool Status);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AGun* GetGun();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

protected:
	virtual void BeginPlay() override;

private:
	AMelee* Melee;

	AMelee* GrabbableMelee;
	
	AGun* Gun;

	bool bIsMeleeEquipped = false;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = "Setup")
	UGrabber* Grabber;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float GrabRange = 500.f;
};
