// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSItemChest.h"

AABSItemChest::AABSItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	LidMesh->SetRelativeLocation(FVector(-35.0f, 0.0f, 50.0f));
	
	TargetPitch = 110.0f;
}

