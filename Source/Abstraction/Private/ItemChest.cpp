// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemChest.h"
#include "Components/StaticMeshComponent.h"

AItemChest::AItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

void AItemChest::OnInteraction(APawn* InstigatorPawn)
{
	bLidOpened = !bLidOpened;
	OnLidOpened();
}

void AItemChest::OnLidOpened()
{
	float CurrPitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}


