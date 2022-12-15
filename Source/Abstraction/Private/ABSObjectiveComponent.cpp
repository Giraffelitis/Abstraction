// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveComponent.h"
#include "ABSInteractionComponent.h"
#include "ABSObjectiveWorldSubsystem.h"
#include "Engine/World.h"

UABSObjectiveComponent::UABSObjectiveComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UABSObjectiveComponent::UpdateObjectiveTag()
{
	if (!this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed")))
	{
		if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Failed")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Failed Objective has been reset");
			this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
			OnStateChanged.Broadcast(this);
			this->ObjectiveTags.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Failed"));
		}
	
		if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.NotAvailableYet")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "New Objective Available");
			this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
			OnStateChanged.Broadcast(this);
			this->ObjectiveTags.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.NotAvailableYet"));		
		}
	
		if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Objective added to Log");
			this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"));
			OnStateChanged.Broadcast(this);
			this->ObjectiveTags.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
		}
	
		if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress")))
		{
			if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Interact.Activate")))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Objective Completed");
				this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed"));
				OnStateChanged.Broadcast(this);
				this->ObjectiveTags.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"));
			}
		}

		if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.ReadyToTurnIn")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Objective is completed");
			this->ObjectiveTags.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed"));
			OnStateChanged.Broadcast(this);
			this->ObjectiveTags.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.ReadyToTurnIn"));
		}		
	}
	else if (this->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Objective added to History Log");
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