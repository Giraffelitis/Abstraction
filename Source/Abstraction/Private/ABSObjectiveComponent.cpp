// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveComponent.h"
#include "ABSInteractionComponent.h"
#include "ABSObjectiveSubsystem.h"
#include "ABSPlayerCharacter.h"
#include "Engine/World.h"

UABSObjectiveComponent::UABSObjectiveComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UABSObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//register
	UABSObjectiveSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UABSObjectiveSubsystem>();
	if (ObjectiveSubsystem)
	{
		UABSObjectiveData* ObjData = ObjectiveData;
		if (ObjData)
		ObjectiveSubsystem->AddObjective(this, ObjData);		
	}

	ResetObjective();
}

void UABSObjectiveComponent::OnObjectiveInteractWith()
{
		OnObjectiveUpdate();
}

void UABSObjectiveComponent::OnObjectiveUpdate()
{
	UABSObjectiveSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UABSObjectiveSubsystem>();
	
	if(!bObjectiveGiver)
	{
		if(GetObjectiveState() != FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress")) return;			
		
		if (GetObjectiveState() != FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed"))
		{
			ObjectiveData->ObjectiveData.ObjectiveState = (FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed"));

			if (ObjectiveSubsystem)
			{
				ObjectiveSubsystem->UpdateObjectiveList();
			}
			OnStateChanged.Broadcast(this);
		}
		else
		{
			if (ObjectiveSubsystem)
			{
				ObjectiveSubsystem->UpdateObjectiveList();
			}
			
			OnStateChanged.Broadcast(this);
		}
	}
	else
	{
		if(GetObjectiveState() != (FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"))) return;
				
		ObjectiveData->ObjectiveData.ObjectiveState = (FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"));

		if (ObjectiveSubsystem)
		{
			ObjectiveSubsystem->UpdateObjectiveList();
		}
		OnStateChanged.Broadcast(this);
	}

};

void UABSObjectiveComponent::ResetObjective()
{
	if(ObjectiveData)
		ObjectiveData->ObjectiveData.ObjectiveState = (FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
}

FGameplayTag UABSObjectiveComponent::GetObjectiveState()
{
	return ObjectiveData->ObjectiveData.ObjectiveState;
}