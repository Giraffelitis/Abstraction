// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionComponent.h"
#include "ABSObjectiveComponent.h"

UABSInteractionComponent::UABSInteractionComponent()
{
	ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Unknown"));
}

bool UABSInteractionComponent::InteractedWith(AActor* InstigatingActor)
{
	UE_LOG(LogTemp, Log, TEXT("InteractionComponent::InteractedWith Function triggered"))
	ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Unknown"));

	OnInteractedWith.Broadcast(InstigatingActor);
	
	//If its secured check if player has the proper key to open it
	if(this->RequiredSecurityTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag")))
	{
		check(InstigatingActor)
	 	UABSInteractionComponent* Comp = InstigatingActor->FindComponentByClass<UABSInteractionComponent>();
	 	if(Comp)
			if(Comp->ActiveGameplayTags.HasAll(this->RequiredSecurityTags))
			{
				if(ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Blocked")))
				{
					ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Blocked"));
				}
				
				ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Available"));
				
				CheckInteractionSuccess(InstigatingActor);
				return true;
			}
	 	
			ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Blocked"));

			OnInteractionFailure.Broadcast(InstigatingActor);
			return false;
	}
	
	ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Available"));
	
	CheckInteractionSuccess(InstigatingActor);
	return true;	
}

void UABSInteractionComponent::CheckInteractionSuccess(AActor* InstigatingActor) const
{
	if(this->GrantedSecurityTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag")))
	{
		check(InstigatingActor)
				 UABSInteractionComponent* Comp = InstigatingActor->FindComponentByClass<UABSInteractionComponent>();
		if(Comp)
		{
			Comp->ActiveGameplayTags.AppendTags(GrantedSecurityTags);
		}
	}
	
	OnInteractionSuccess.Broadcast(InstigatingActor);
}

