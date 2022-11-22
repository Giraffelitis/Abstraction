// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjective.h"
#include "ABSObjectiveComponent.h"

void UABSObjective::Initialize(UABSObjectiveComponent* NewObjectiveComp)
{
	ObjectiveComp = NewObjectiveComp;
}

bool UABSObjective::CanStart_Implementation(AActor* Instigator)
{
	UABSObjectiveComponent* Comp = GetOwningComponent();
	
	if (Comp->ObjectiveTags.HasAny(BlockingTags))
	{
		return false;
	}

	return true;
}

void UABSObjective::StartObjective_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Started: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UABSObjectiveComponent* Comp = GetOwningComponent();	
	Comp->ObjectiveTags.AppendTags(GrantsTags);

	if (GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		//TimeStarted = GetWorld()->TimeSeconds;
	}

	GetOwningComponent()->OnObjectiveStarted.Broadcast(GetOwningComponent(), this);
}

void UABSObjective::CompleteObjective_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);

	UABSObjectiveComponent* Comp = GetOwningComponent();
	Comp->ObjectiveTags.RemoveTags(GrantsTags);

	GetOwningComponent()->OnObjectiveCompleted.Broadcast(GetOwningComponent(), this);
}

UABSObjectiveComponent* UABSObjective::GetOwningComponent() const
{
	return ObjectiveComp;
}