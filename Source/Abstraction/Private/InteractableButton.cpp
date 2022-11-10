// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableButton.h"
#include "ButtonInteractionComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

AInteractableButton::AInteractableButton() : Super()
{
	ButtonInteractionComponent = CreateDefaultSubobject<UButtonInteractionComponent>(TEXT("ButtonInteractionComponent"));
	if (ButtonInteractionComponent->GetTriggerCapsule())
	{
		ButtonInteractionComponent->GetTriggerCapsule()->SetupAttachment(RootComponent);
	}
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AInteractableButton::BeginPlay()
{
	Super::BeginPlay();
	ButtonInteractionComponent->InteractionSuccess.AddDynamic(this, &AInteractableButton::OnInteractionSuccess);
}

void AInteractableButton::PressButton()
{
	ButtonInteractionComponent->PressButton();
}

void AInteractableButton::OnInteractionSuccess()
{
	OnButtonPressed.Broadcast();
}