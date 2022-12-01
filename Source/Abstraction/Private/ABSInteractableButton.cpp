// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableButton.h"
#include "ABSInteractionComponent.h"

AABSInteractableButton::AABSInteractableButton()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(FrameMesh);
	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	
	DepressDepth = 4;
}

void AABSInteractableButton::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		StartInteract();
	}
}

void AABSInteractableButton::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSInteractableButton::OnInteraction);
}

void AABSInteractableButton::OnInteraction(AActor* InstigatingActor)
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

void AABSInteractableButton::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSInteractableButton::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSInteractableButton::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableButton::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}

