// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveComponent.h"
#include "ABSObjectiveWorldSubsystem.h"
#include "Engine/World.h"

UABSObjectiveComponent::UABSObjectiveComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Inactive"));
}

void UABSObjectiveComponent::UpdateObjectiveTag()
{
	if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Inactive")))
	{
		this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Active"));
		OnStateChanged.Broadcast(this);
	}
}


void UABSObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//register
	UABSObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UABSObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}

void UABSObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UABSObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UABSObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}