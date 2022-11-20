// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionTags.h"
#include "ABSInteractionComponent.h"

void UABSInteractionTags::Initialize(UABSInteractionComponent* NewActionComp)
{
	InteractionComp->ActiveGameplayTags.AppendTags(InteractionTags);
	InteractionComp->ActiveGameplayTags.AppendTags(SecurityTags);
	InteractionComp = NewActionComp;
}

bool UABSInteractionTags::CanStart_Implementation(AActor* Instigator)
{
	UABSInteractionComponent* Comp = GetOwningComponent();
	
	if (Comp->ActiveGameplayTags.HasAny(SecurityTags))
	{

		// Need to check for character security tags here to see if it can be activated
		
		return false;
	}

	return true;
}

void UABSInteractionTags::StartInteraction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Started: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UABSInteractionComponent* Comp = GetOwningComponent();	
	Comp->ActiveGameplayTags.AppendTags(InteractionTags);

//	GetOwningComponent()->OnInteractionStarted.Broadcast(GetOwningComponent(), this);
}

UABSInteractionComponent* UABSInteractionTags::GetOwningComponent() const
{
	return InteractionComp;
}