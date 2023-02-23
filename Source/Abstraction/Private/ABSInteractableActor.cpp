// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractableActor.h"
#include "ABSInteractionComponent.h"

// Sets default values
AABSInteractableActor::AABSInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
}

void AABSInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Activated")))
	{
		APawn* MyPawn = Cast<APawn>(GetOwner());
		Execute_InteractionStart(this, MyPawn);
	}
}

void AABSInteractableActor::BindWithComponent()
{
	InteractionComp->OnInteractionSuccess.AddDynamic(this, &AABSInteractableActor::OnInteraction);
}

void AABSInteractableActor::OnInteraction(AActor* InstigatingActor)
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	//If its activated deactivate it and remove tag		Else add tag and Activate it.
	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Activated")))
	{
		InteractionComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Activated"));
		Execute_InteractionEnd(this, MyPawn);
	}
	else
	{
		InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Activated"));
		Execute_InteractionStart(this, MyPawn);
	}

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.State.Collectible")))
	{
		
	}
}

UABSInteractionComponent* AABSInteractableActor::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableActor::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}