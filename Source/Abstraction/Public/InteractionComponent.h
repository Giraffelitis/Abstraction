// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UENUM()
enum class EInteractionState
{
	IS_Off = 0	UMETA(DisplayName = "Off"),
	IS_On = 1	UMETA(DisplayName = "On")
};

class IConsoleVariable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_EVENT(FInteractionComponent, FActivated)
	FActivated& IsSwitchedOn() { return ActivatedEvent; }
	FActivated ActivatedEvent;

	DECLARE_EVENT(FInteractionComponent, FDeactivated)
	FActivated& IsSwitchedOff() { return DeactivatedEvent; }
	FActivated DeactivatedEvent;

	void ToggleOn();
	void ToggleOff();
	void DebugDraw();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool IsToggledOn = false;

	UPROPERTY(EditAnywhere)
	bool IsOnTimer = false;

	UPROPERTY(EditAnywhere)
	float TurnOffTimerDuration = 1.0f;
	float CurrentTimerDuration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	EInteractionState InteractionState;

};

