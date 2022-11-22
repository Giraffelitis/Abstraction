// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABSPlayerCharacter.generated.h"

struct FInputActionValue;
class UABSInputConfig;
class UABSInteractAction;
class UCameraComponent;
class UCameraShakeBase;
class UGameplayTagsManager;
class UABSAttributeComponent;
class UParticleSystemComponent;
class UABSActionComponent;
class UABSInteractionComponent;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS()
class ABSTRACTION_API AABSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABSPlayerCharacter();

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCameraComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called when the actor falls out of the world 'safely' (below KillZ and such) */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	
	UPROPERTY(VisibleAnywhere)
	UABSInteractAction* InteractAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSAttributeComponent* AttributeComp;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSActionComponent* ActionComp;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UABSInputConfig* InputConfig;	

	/** Handles moving forward/backward/left/right */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

	void SprintStart(const FInputActionValue& InputActionValue);

	void SprintStop(const FInputActionValue& InputActionValue);

	void PrimaryAttack(const FInputActionValue& InputActionValue);
	
	void SecondaryAttack(const FInputActionValue& InputActionValue);

	void Parry(const FInputActionValue& InputActionValue);

	void PrimaryInteract(const FInputActionValue& InputActionValue);

	void SecondaryInteract(const FInputActionValue& InputActionValue);
	
protected:

	UPROPERTY(VisibleAnywhere)
	UABSInteractionComponent* InteractionComp;

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
