// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableDoor.h"
#include "Components/AudioComponent.h"

AInteractableDoor::AInteractableDoor()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);

	TargetOpenAngle = 110;
}

void AInteractableDoor::OnInteraction(APawn* InstigatorPawn)
{
	bDoorOpened = !bDoorOpened;
	OnDoorOpened();
}

void AInteractableDoor::OnDoorOpened()
{
	float CurrAngle = bDoorOpened ? TargetOpenAngle : 0.0f;
	DoorMesh->SetRelativeRotation(FRotator(0, 0, CurrAngle));
}

