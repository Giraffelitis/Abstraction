// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableButton.h"
#include "InteractionComponent.h"

AInteractableButton::AInteractableButton()
{
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}