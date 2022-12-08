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

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		StartInteract();
	}
}

void AABSInteractableActor::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSInteractableActor::OnInteraction);
}

void AABSInteractableActor::OnInteraction(AActor* InstigatingActor)
{	
	//If its activated deactivate it and remove tag		Else add tag and Activate it.
	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		InteractionComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated"));
		EndInteract();
	}
	else
	{
		InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated"));
		StartInteract();
	}
}

void AABSInteractableActor::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSInteractableActor::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSInteractableActor::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableActor::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}