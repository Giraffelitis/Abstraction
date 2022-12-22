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
		FName ObjID = ObjectiveData->ObjectiveData.ObjectiveID;
		ObjectiveSubsystem->AddObjective(ObjID);
	}
}

void UABSObjectiveComponent::OnObjectiveInteract()
{
	UABSObjectiveSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UABSObjectiveSubsystem>();
	if(!bObjectiveGiver)
	{	
		if(!ObjectiveData->ObjectiveData.ObjectiveState.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"))) return;			
		
		if (!ObjectiveData->ObjectiveData.bIsCompleted)
		{			
			ObjectiveData->ObjectiveData.ObjectiveState.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"));
			ObjectiveData->ObjectiveData.ObjectiveState.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed"));

			OnStateChanged.Broadcast(this);
			if (ObjectiveSubsystem)
			{
				ObjectiveSubsystem->UpdateObjectiveList();
			}
			
			ObjectiveData->ObjectiveData.bIsCompleted = true;
		}
		else
		{
			OnStateChanged.Broadcast(this);
			if (ObjectiveSubsystem)
			{
				ObjectiveSubsystem->UpdateObjectiveList();
			}
		}
	}
	else
	{
		if(!ObjectiveData->ObjectiveData.ObjectiveState.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"))) return;
				
		ObjectiveData->ObjectiveData.ObjectiveState.RemoveTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
		ObjectiveData->ObjectiveData.ObjectiveState.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"));

		OnStateChanged.Broadcast(this);
		if (ObjectiveSubsystem)
		{
			ObjectiveSubsystem->UpdateObjectiveList();
		}
	}
};


void UABSObjectiveComponent::ResetObjective()
{
	ObjectiveData->ObjectiveData.ObjectiveState.AddTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Available"));
	ObjectiveData->ObjectiveData.bIsCompleted = false;
}
