// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController())
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
		{
			CurrentRotationTime += DeltaTime;
			const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
			const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
			const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
			GetOwner()->SetActorRotation(CurrentRotation);
		}
		else if (GetOwner()->GetActorRotation() != CloseRotation && CurrentRotationTime > 0)
		{
			if (CurrentRotationTime > TimeToRotate)
			{
				CurrentRotationTime = TimeToRotate;
			}

			CurrentRotationTime -= DeltaTime;
			const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
			const float RotationAlpha = CloseCurve.GetRichCurveConst()->Eval(TimeRatio);
			const FRotator CurrentRotation = FMath::Lerp(GetOwner()->GetActorRotation(), CloseRotation, RotationAlpha);
			GetOwner()->SetActorRotation(CurrentRotation);

			if (CurrentRotation == CloseRotation)
			{
				CurrentRotationTime = 0.0f;
			}
		}
	}
		
	

	
	// ...
}

