// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableElevator.h"
#include "Components/AudioComponent.h"

AInteractableElevator::AInteractableElevator()
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

void AInteractableElevator::OnInteraction(APawn* InstigatorPawn)
{
	bButtonPressed = !bButtonPressed;
	OnButtonPressed();
}

void AInteractableElevator::OnButtonPressed()
{
	float CurrHeight = bButtonPressed ? LiftHeight : 0.0f;
	PlatformMesh->SetRelativeLocation(FVector(0, 0, CurrHeight));
}
