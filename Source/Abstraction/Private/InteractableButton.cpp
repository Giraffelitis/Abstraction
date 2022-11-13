// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableButton.h"
#include "ButtonInteractionComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

AInteractableButton::AInteractableButton() : Super()
{
	ButtonInteractionComponent = CreateDefaultSubobject<UButtonInteractionComponent>(TEXT("ButtonInteractionComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerComponent"));
	TriggerCapsule->SetupAttachment(RootComponent);
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