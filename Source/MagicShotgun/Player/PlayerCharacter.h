// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Mannequin.h"
#include "PlayerCharacter.generated.h"

class UGrabber;
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
	void GrabItem();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	USkeletalMeshComponent* GetMesh1P();

protected:
	virtual void BeginPlay() override;

private:
	bool CanGrabItem();

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun* Gun;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = "Setup")
	UGrabber* Grabber;
};