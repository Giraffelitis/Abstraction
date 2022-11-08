// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
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
UDoorInteractionComponent::UDoorInteractionComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Closed;
	DoorSwing = EDoorSwing::Swing_In;
}


void UDoorInteractionComponent::InteractionStart()
{
	Super::InteractionStart();
	if (InteractingActor)
	{
		OpenDoor();
	}
}

// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	CloseRotation = GetOwner()->GetActorRotation();
	// ensure TimeToRotate is greater than EPSILON
	CurrentRotationTime = 0.0f;
}

void UDoorInteractionComponent::OpenDoor()
{
	if (IsOpen() || DoorState == EDoorState::DS_Opening)
	{
		return;
	}
	DoorState = EDoorState::DS_Opening;
	CurrentRotationTime = 0.0f;
}

void UDoorInteractionComponent::CloseDoor()
{
	if (IsClosed() || DoorState == EDoorState::DS_Closing)
	{
		return;
	}
	DoorState = EDoorState::DS_Closing;
	CurrentRotationTime = 0.0f;
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (DoorState == EDoorState::DS_Opening)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, GetDoorSwing(PlayerPawn), RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorOpened();
		}
	}	
	else if (DoorState == EDoorState::DS_Open)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController())
		{
			if (PlayerPawn && !TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_Closing;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Closing)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = CloseCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(GetOwner()->GetActorRotation(), CloseRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorClosed();
		}
	}	
}

//When door is opened set state to open check for objectives tied to door and complete them if applicable
// Prints debug info to screen and tells any listeners that the interaction was successful
void UDoorInteractionComponent::OnDoorOpened()
{
	DoorState = EDoorState::DS_Open;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
	InteractionSuccess.Broadcast();
}

//When door is closed set state to closed check for objectives tied to door and complete them if applicable
// Prints debug info to screen and tells any listeners that the interaction was successful
void UDoorInteractionComponent::OnDoorClosed()
{
	DoorState = EDoorState::DS_Closed;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorClosed"));
	InteractionSuccess.Broadcast();
}

// Gets player facing direction compared to door location and sets the rotation accordingly
FRotator UDoorInteractionComponent::GetDoorSwing(APawn* pawn)
{
	float SwingDirection = FVector::DotProduct(GetOwner()->GetActorLocation(), pawn->GetActorForwardVector());
	
	if (SwingDirection > 0)
	{
		const FRotator ReverseRotation = FinalRotation * (0.0f, 0.0f, -1.0f);
		return ReverseRotation;
	}
	return FinalRotation;
}

