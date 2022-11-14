// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.h"
#include "Engine/World.h"
#include "AbstractionGameplayTags.h"
#include "NativeGameplayTags.h"

UObjectiveComponent::UObjectiveComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}


void UObjectiveComponent::SetState()
{
//	if (.Objective_Inactive)
//	{
//		State = NewState;
//		OnStateChanged.Broadcast(this, NewState);
//	}
}


void UObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//register
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}


void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}
