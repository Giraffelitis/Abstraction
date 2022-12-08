// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableElevator.h"

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
