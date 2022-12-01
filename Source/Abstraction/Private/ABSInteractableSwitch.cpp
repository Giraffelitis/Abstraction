// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractableSwitch.h"
#include "ABSInteractionComponent.h"
#include "Components/AudioComponent.h"

AABSInteractableSwitch::AABSInteractableSwitch()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetRelativeRotation(FRotator(-35.0f, 0.0f, 50.0f));
	SwitchMesh->SetupAttachment(BaseMesh);
	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	
	SwitchAngle = 50;

}

void AABSInteractableSwitch::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("InteractionTag.Activated")))
	{
		StartInteract();
	}
}

void AABSInteractableSwitch::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSInteractableSwitch::OnInteraction);
}

void AABSInteractableSwitch::OnInteraction(AActor* InstigatingActor)
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

void AABSInteractableSwitch::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSInteractableSwitch::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSInteractableSwitch::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSInteractableSwitch::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}

