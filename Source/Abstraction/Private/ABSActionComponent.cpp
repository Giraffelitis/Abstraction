// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSActionComponent.h"
#include "ABSAction.h"

UABSActionComponent::UABSActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UABSActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Server Only
	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<UABSAction> ActionClass : DefaultActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}


void UABSActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Stop all
	TArray<UABSAction*> ActionsCopy = Actions;
	for (UABSAction* Action : ActionsCopy)
	{
		if (Action )
		{
			Action->StopAction(GetOwner());
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UABSActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UABSActionComponent::AddAction(AActor* Instigator, TSubclassOf<UABSAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	// Skip for clients
	if (!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client attempting to AddAction. [Class: %s]"), *GetNameSafe(ActionClass));
		return;
	}

	UABSAction* NewAction = NewObject<UABSAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);

		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}


void UABSActionComponent::RemoveAction(UABSAction* ActionToRemove)
{
	if (!ensure(ActionToRemove ))
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}


UABSAction* UABSActionComponent::GetAction(TSubclassOf<UABSAction> ActionClass) const
{
	for (UABSAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}


bool UABSActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UABSAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}
			// Bookmark for Unreal Insights
			TRACE_BOOKMARK(TEXT("StartAction::%s"), *GetNameSafe(Action));

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}


bool UABSActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UABSAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
				Action->StopAction(Instigator);
				return true;
		}
	}

	return false;
}

