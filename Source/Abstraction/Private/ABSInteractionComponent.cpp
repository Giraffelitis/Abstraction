// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractionComponent.h"

void UABSInteractionComponent::InteractedWith(AActor* FocusedActor) const
{
	UE_LOG(LogTemp, Log, TEXT("InteractionComponent::InteractedWith Function triggered"))
	OnInteractedWith.Broadcast(FocusedActor);
}