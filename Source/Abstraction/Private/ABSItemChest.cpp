// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSItemChest.h"
#include "Components/StaticMeshComponent.h"

AABSItemChest::AABSItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	bLidOpened = true;
	TargetPitch = 110;
}

void AABSItemChest::OnInteraction(APawn* InstigatorPawn)
{
	bLidOpened = !bLidOpened;
	OnLidOpened();
}

void AABSItemChest::OnLidOpened()
{
	float CurrPitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}