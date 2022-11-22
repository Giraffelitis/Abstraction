// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableDoor.h"
#include "ABSInteractionComponent.h"
#include "Components/AudioComponent.h"

AABSInteractableDoor::AABSInteractableDoor()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);

	TargetOpenAngle = 110;
}

void AABSInteractableDoor::OnInteraction(APawn* InstigatorPawn)
{
	bDoorOpened = !bDoorOpened;
	OnDoorOpened();
}

void AABSInteractableDoor::OnDoorOpened()
{
	float CurrAngle = bDoorOpened ? TargetOpenAngle : 0.0f;
	DoorMesh->SetRelativeRotation(FRotator(0, 0, CurrAngle));
}

