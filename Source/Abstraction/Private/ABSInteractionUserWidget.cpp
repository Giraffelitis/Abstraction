// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionUserWidget.h"

#include "ABSInteractionComponent.h"

void UABSInteractionUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UABSInteractionComponent* InteractionComp = AttachedActor->FindComponentByClass<UABSInteractionComponent>();
	if(InteractionComp)
	{
		if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Blocked")))
		{
			InteractMessage = InteractionComp->InteractFailMessage;
		}
		else
		{
			InteractMessage = InteractionComp->InteractSuccessMessage;
		}
	}
}
