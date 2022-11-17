// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractableElevator.h"
#include "Components/AudioComponent.h"

AABSInteractableElevator::AABSInteractableElevator()
{
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	BackRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRailingMesh"));
	BackRailingMesh->SetupAttachment(PlatformMesh);
	LeftRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftRailingMesh"));
	LeftRailingMesh->SetupAttachment(PlatformMesh);
	RightRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightRailingMesh"));
	RightRailingMesh->SetupAttachment(PlatformMesh);

	LiftHeight = 1000;
}

void AABSInteractableElevator::OnInteraction(APawn* InstigatorPawn)
{
	bElevatorActivated = !bElevatorActivated;
	OnElevatorActivated();
}

void AABSInteractableElevator::OnElevatorActivated()
{
	float CurrHeight = bElevatorActivated ? LiftHeight : 0.0f;
	PlatformMesh->SetRelativeLocation(FVector(0, 0, CurrHeight));
}
