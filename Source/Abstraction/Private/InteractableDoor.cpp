// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableDoor.h"
#include "DoorInteractionComponent.h"
#include "Components/CapsuleComponent.h"

AInteractableDoor::AInteractableDoor() : Super()
{
	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteractionComponent"));
	if (DoorInteractionComponent->GetTriggerCapsule())
	{
		//Commented out sections are an attempt to adjust the attach location for the Trigger Capsule
		//FVector Offset(-50.0f, 0.0f, 100.0f);
		//FVector AttachLocation = GetOwner()->GetActorLocation() + Offset;

		DoorInteractionComponent->GetTriggerCapsule()->SetupAttachment(RootComponent);  
		//DoorInteractionComponent->GetTriggerCapsule()->SetRelativeLocation(AttachLocation);
	}
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorInteractionComponent->InteractionSuccess.AddDynamic(this, &AInteractableDoor::OnInteractionSuccess);
}

void AInteractableDoor::OnInteractionSuccess()
{
	OnDoorOpen.Broadcast();
}