// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

struct FInputActionValue;
class UInteractionComponent;
class UInputConfig;
class UCameraShakeBase;
class UDamageHandlerComponent;
class UGameplayTagsManager;
class UHealthComponent;
class UParticleSystemComponent;

UCLASS()
class ABSTRACTION_API AAbstractionPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AAbstractionPlayerCharacter();

	/** Default UObject constructor. */
	AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called when the actor falls out of the world 'safely' (below KillZ and such) */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Abstraction")
	void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

	UFUNCTION(BlueprintCallable)
	void HandleItemCollected();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemCollected();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ItemsCollected = 0;
	
	//this can be an array or moved later as needed
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputConfig* InputConfig;	

	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

	/** Handles Pew Pew */
	void Input_Fire(const FInputActionValue& InputActionValue);

	/** Handles Interaction */
	void Input_Interact(const FInputActionValue& InputActionValue);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;
	
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

	void PrimaryInteract();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere)
	UDamageHandlerComponent* DamageHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* InteractionComp;
	
	APlayerController* PC;

	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UCameraShakeBase> CamShake;

	// Force Feedback values.
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackIntensity = 1.0f;
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackDuration = 1.0f;
};
