// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSwitch.h"
#include "Components/AudioComponent.h"

AInteractableSwitch::AInteractableSwitch()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(BaseMesh);

	DepressDepth = 10;

}

void AInteractableSwitch::OnInteraction(APawn* InstigatorPawn)
{
	bSwitchedOn = !bSwitchedOn;
	OnSwitchedOn();
}

void AInteractableSwitch::OnSwitchedOn()
{
	float CurrDepth = bSwitchedOn ? DepressDepth : 0.0f;
	SwitchMesh->SetRelativeRotation(FRotator(0, 0, 0));
}

