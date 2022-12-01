// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSInteractableElevator.h"
#include "ABSInteractionComponent.h"

AABSInteractableElevator::AABSInteractableElevator()
{
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	BackRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRailingMesh"));
	BackRailingMesh->SetupAttachment(PlatformMesh);
	LeftRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftRailingMesh"));
	LeftRailingMesh->SetupAttachment(PlatformMesh);
	RightRailingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightRailingMesh"));
	RightRailingMesh->SetupAttachment(PlatformMesh);
	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
		
	LiftHeight = 1000;
}

void AABSInteractableElevator::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		StartInteract();
	}
}

void AABSInteractableElevator::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSInteractableElevator::OnInteraction);
}

void AABSInteractableElevator::OnInteraction(AActor* InstigatingActor)
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

void AABSInteractableElevator::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSInteractableElevator::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSInteractableElevator::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableElevator::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}