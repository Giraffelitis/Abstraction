// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractableSwitch.h"
#include "Components/AudioComponent.h"

AABSInteractableSwitch::AABSInteractableSwitch()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetRelativeRotation(FRotator(-35.0f, 0.0f, 50.0f));
	SwitchMesh->SetupAttachment(BaseMesh);
	SwitchAngle = 50;

}

void AABSInteractableSwitch::OnInteraction(APawn* InstigatorPawn)
{
	bSwitchedOn = !bSwitchedOn;
	OnSwitchedOn();
}

void AABSInteractableSwitch::OnSwitchedOn()
{
	float CurrAngle = bSwitchedOn ? SwitchAngle : 0.0f;
	SwitchMesh->SetRelativeRotation(FRotator(0, CurrAngle, 0));
}

