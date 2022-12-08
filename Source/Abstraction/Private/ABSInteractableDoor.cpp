// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableDoor.h"

AABSInteractableDoor::AABSInteractableDoor()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);
	
	TargetOpenAngle = 110;
}
