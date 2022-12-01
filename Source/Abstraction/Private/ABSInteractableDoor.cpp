// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableDoor.h"
#include "ABSInteractionComponent.h"
#include "Components/AudioComponent.h"

AABSInteractableDoor::AABSInteractableDoor()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);
	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	
	TargetOpenAngle = 110;
}

void AABSInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		StartInteract();
	}
}

void AABSInteractableDoor::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSInteractableDoor::OnInteraction);
}

void AABSInteractableDoor::OnInteraction(AActor* InstigatingActor)
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

void AABSInteractableDoor::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSInteractableDoor::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSInteractableDoor::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableDoor::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}
