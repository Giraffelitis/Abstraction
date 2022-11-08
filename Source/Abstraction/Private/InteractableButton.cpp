// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableButton.h"
#include "ObjectiveWorldSubsystem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ObjectiveComponent.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("Abstraction.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display"),
	ECVF_Default);

// Sets default values for this component's properties
UInteractableButton::UInteractableButton()
{
	PrimaryComponentTick.bCanEverTick = true;
	ButtonState = EButtonState::BS_Out;
}

void UInteractableButton::InteractionStart()
{
	Super::InteractionStart();
	if (InteractingActor)
	{
		ButtonPressed();
	}
}

// Called when the game starts
void UInteractableButton::BeginPlay()
{
	Super::BeginPlay();
	// ensure CurrentPressedTime is greater than EPSILON
	CurrentPressedTime = 0.0f;
}

void UInteractableButton::ButtonPressed()
{
	if (IsPressed() || ButtonState == EButtonState::BS_In)
	{
		return;
	}
	ButtonState = EButtonState::BS_In;
	CurrentPressedTime = 0.0f;
}

void UInteractableButton::ButtonReleased()
{
	if (IsNotPressed() || ButtonState == EButtonState::BS_Out)
	{
		return;
	}
	ButtonState = EButtonState::BS_Out;
	CurrentPressedTime = 0.0f;
}

// Called every frame
void UInteractableButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ButtonState == EButtonState::BS_In)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		CurrentPressedTime += DeltaTime;
		// *** Need to add it button pressed animation here. 
		if (CurrentPressedTime >= TimeToRelease)
		{
			ButtonReleased();
		}
	}
}

//When button is pressed set state to in check for objectives tied to door and complete them if applicable
// Prints debug info to screen and tells any listeners that the interaction was successful
void UInteractableButton::OnButtonPressed()
{
	ButtonState = EButtonState::BS_In;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("ButtonPressed"));
	InteractionSuccess.Broadcast();
}

//When button is released set state to out and check for objectives tied to door and complete them if applicable
// Prints debug info to screen and tells any listeners that the interaction was successful
void UInteractableButton::OnButtonReleased()
{
	ButtonState = EButtonState::BS_Out;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("ButtonReleased"));
	InteractionSuccess.Broadcast();
}
