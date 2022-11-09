// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "ObjectiveWorldSubsystem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugInteraction(
	TEXT("Abstraction.InteractionComponent.Debug"),
	false,
	TEXT("Toggle InteractionComponent debug display"),
	ECVF_Default);

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (IsToggledOn == true)
	{
		InteractionState = EInteractionState::IS_On;
	}
	else
	{
		InteractionState = EInteractionState::IS_Off;
	}

	CurrentTimerDuration = 0.0f;

}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InteractionState == EInteractionState::IS_Off)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && !IsToggledOn)
		{
			ToggleOn();
			if (IsOnTimer)
			{
				CurrentTimerDuration = 0.0f;
			}
		}
	}
	else if (InteractionState == EInteractionState::IS_On)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && IsToggledOn)
		{
			if (!IsOnTimer)
			{
				ToggleOff();
			}
		}
	}
	if (InteractionState == EInteractionState::IS_On)
	{
		if (CurrentTimerDuration < TurnOffTimerDuration)
		{
			CurrentTimerDuration += DeltaTime;
		}
		else
		{
			ToggleOff();
		}
	}
	DebugDraw();
}

void UInteractionComponent::ToggleOn()
{
	InteractionState = EInteractionState::IS_On;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("On"));
}

void UInteractionComponent::ToggleOff()
{
	InteractionState = EInteractionState::IS_Off;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Off"));
}

void UInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugInteraction->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(0.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Interaction State:") + UEnum::GetDisplayValueAsText(InteractionState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}

