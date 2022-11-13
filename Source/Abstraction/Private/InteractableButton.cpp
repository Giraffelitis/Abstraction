// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableButton.h"
#include "Components/AudioComponent.h"

AInteractableButton::AInteractableButton()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	ButtonMesh->SetupAttachment(FrameMesh);

	DepressDepth = 10;
}

void AInteractableButton::OnInteraction(APawn* InstigatorPawn)
{
	bButtonPressed = !bButtonPressed;
	OnButtonPressed();
}

void AInteractableButton::OnButtonPressed()
{
	float CurrDepth = bButtonPressed ? DepressDepth : 0.0f;
	ButtonMesh->SetRelativeRotation(FRotator(0, 0, 0));
}

