// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionComponent.h"
#include "ABSObjectiveComponent.h"
#include "ABSObjectiveWorldSubsystem.h"

void UABSInteractionComponent::InteractedWith(AActor* InstigatingActor)
{
	UE_LOG(LogTemp, Log, TEXT("InteractionComponent::InteractedWith Function triggered"))

	UABSObjectiveComponent* ObjectiveComp = InstigatingActor->FindComponentByClass<UABSObjectiveComponent>();
	//If its secured check if player has the proper key to open it
	 if(this->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag")))
	{
		check(InstigatingActor)
	 	UABSInteractionComponent* Comp = InstigatingActor->FindComponentByClass<UABSInteractionComponent>();
		if(Comp->ActiveGameplayTags.HasAllExact(this->SecurityTags))
		{
			OnInteractedWith.Broadcast(InstigatingActor);
		}
		else
		{			
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Security Requirements not met");
		}
	}
	 else
	 {
	 	OnInteractedWith.Broadcast(InstigatingActor);
	 }
}

void UABSInteractionComponent::InteractionSuccessful(AActor* FocusedActor) const
{

}

