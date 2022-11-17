// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABSPlayerCharacter.generated.h"

struct FInputActionValue;
class UABSInputConfig;
class UABSInteractionComponent;
class UCameraShakeBase;
class UGameplayTagsManager;
class UABSAttributeComponent;
class UParticleSystemComponent;
class UABSActionComponent;

UCLASS()
class ABSTRACTION_API AABSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AAbstractionPlayerCharacter();

	/** Default UObject constructor. */
	AABSPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere)
	UABSInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSAttributeComponent* AttributeComp;

	/** Called when the actor falls out of the world 'safely' (below KillZ and such) */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSActionComponent* ActionComp;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void SprintStart();

	void SprintStop();

	void PrimaryAttack();

	void Dash();

	void PrimaryInteract();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Activates primary action of held item. */
	void OnPrimaryAction();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void OnDeath(bool IsFellOut);

	// Force Feedback values.
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackIntensity = 1.0f;
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackDuration = 1.0f;
};
