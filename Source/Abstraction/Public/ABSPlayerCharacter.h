// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABSPlayerCharacter.generated.h"

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

class UABSPortalManager;
struct FInputActionValue;
class UABSObjectiveData;
class USpringArmComponent;
class UCameraComponent;
class UCameraShakeBase;
class UGameplayTagsManager;
class UParticleSystemComponent;
class UBoxComponent;
class UABSInputConfig;
class UABSInteractAction;
class UABSAttributeComponent;
class UABSObjectiveData;
class UABSActionComponent;
class UABSInteractionComponent;
class AABSPlayerController;

UCLASS()
class ABSTRACTION_API AABSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABSPlayerCharacter();
		
	AABSPlayerController* GetPlayerController();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PortalProjectileClass;
	
	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PostTeleportCorrection();

	/** Handles moving forward/backward/left/right */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void SprintStart(const FInputActionValue& InputActionValue);

	void SprintStop(const FInputActionValue& InputActionValue);

	void PrimaryAttack(const FInputActionValue& InputActionValue);
	
	void SecondaryAttack(const FInputActionValue& InputActionValue);

	void Parry(const FInputActionValue& InputActionValue);

	void PrimaryInteract(const FInputActionValue& InputActionValue);

	void SecondaryInteract(const FInputActionValue& InputActionValue);

	/** Called when the actor falls out of the world 'safely' (below KillZ and such) */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSInteractAction* InteractAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSActionComponent* ActionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UABSPortalManager* PortalManagerComp;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UABSInputConfig* InputConfig;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowObjectiveInfo(FObjectiveData Objective);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowObjectiveCompleted(const FText& Message);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowUpdatedObjectiveList(const TArray<FText>& ObjectiveTextList);

	void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	FCollisionProfileName CollisionProfile;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	void OnDeath(bool IsFellOut);

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

	/** Activates primary action of held item. */
	void OnPrimaryAction();

	// Force Feedback values.
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackIntensity = 1.0f;
	
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackDuration = 1.0f;
	
};
