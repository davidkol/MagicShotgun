// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Melee.generated.h"

UCLASS()
class MAGICSHOTGUN_API AMelee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMelee();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* Melee_Weapon;

 	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
 	class USceneComponent* SceneComponent;

	bool bGrabbed = false;

	bool bThrown = false;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float SpeedCoefficient = 1500;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float Durability = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float Reach = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnSwing();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnThrow();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SwitchTo();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SwitchFrom();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ReduceDurability(float DuraDamage);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetDurability();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool GetThrownStatus();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool GetGrabStatus();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetThrownStatus(bool Status);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetReach();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* Swing1Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* Swing2Sound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimSequence* SwingAnimation1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimSequence* SwingAnimation2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimSequence* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UCameraShake> CameraShake1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UCameraShake> CameraShake2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class AActor> DamageComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
};
