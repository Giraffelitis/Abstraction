// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionTags.h"
#include "ABSInteractionTagsComponent.h"

void UABSInteractionTags::Initialize(UABSInteractionTagsComponent* NewActionComp)
{
	InteractionTagsComp->ActiveGameplayTags.AppendTags(InteractionTags);
	InteractionTagsComp->ActiveGameplayTags.AppendTags(SecurityTags);
	InteractionTagsComp = NewActionComp;
}

bool UABSInteractionTags::CanStart_Implementation(AActor* Instigator)
{
	UABSInteractionTagsComponent* Comp = GetOwningComponent();
	
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

	UABSInteractionTagsComponent* Comp = GetOwningComponent();	
	Comp->ActiveGameplayTags.AppendTags(InteractionTags);

//	GetOwningComponent()->OnInteractionStarted.Broadcast(GetOwningComponent(), this);
}

UABSInteractionTagsComponent* UABSInteractionTags::GetOwningComponent() const
{
	return InteractionTagsComp;
}