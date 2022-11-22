// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableButton.h"
#include "ABSInteractionComponent.h"
#include "Components/AudioComponent.h"

AABSInteractableButton::AABSInteractableButton()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(FrameMesh);

	DepressDepth = 4;
}

void AABSInteractableButton::OnInteraction(APawn* InstigatorPawn)
{
	bButtonPressed = !bButtonPressed;
	OnButtonPressed();
}

void AABSInteractableButton::OnButtonPressed()
{
	float CurrDepth = bButtonPressed ? DepressDepth : 0.0f;
	ButtonMesh->SetRelativeLocation(FVector(0, CurrDepth, 0));
}

