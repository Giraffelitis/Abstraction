// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "IDetailTreeNode.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

class UDamageHandlerComponent;
class UHealthComponent;
class UParticleSystemComponent;

//these are input bindings
DECLARE_MULTICAST_DELEGATE(FInteractionStartRequest);
DECLARE_MULTICAST_DELEGATE(FInteractionCancelRequest);

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

	//bindings, a hack atm as the interactble components in the game world get the player and sign themselves up to these events
	//to know when the player has pressed the input binding for interacting
	FInteractionStartRequest OnInteractionStartRequested;
	FInteractionCancelRequest OnInteractionCancelRequested;

	UFUNCTION(BlueprintImplementableEvent)
	void DoorOpenInteractionStarted(AActor* InteractableActor);

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonPressInteractionStarted(AActor* InteractableActor);

	//this can be an array or moved later as needed
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	//Input Bindings
	void InteractionStartRequested();
	void InteractionCancelRequested();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere)
	UDamageHandlerComponent* DamageHandlerComponent;

	APlayerController* PC;

	//UPROPERTY(EditAnywhere, Category="Effects")
	//TSubclassOf<UCameraShake> CamShake;

	// Force Feedback values.
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackIntensity = 1.0f;
	UPROPERTY(EditAnywhere, Category="Force Feedback")
	float ForceFeedbackDuration = 1.0f;
	
};
