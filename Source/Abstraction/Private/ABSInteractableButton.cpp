// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableButton.h"

AABSInteractableButton::AABSInteractableButton()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(FrameMesh);
	
	DepressDepth = 4;
}