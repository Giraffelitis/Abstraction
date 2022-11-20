// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSItemChest.h"
#include "ABSAction.h"
#include "ABSInteractionComponent.h"
#include "Components/StaticMeshComponent.h"

AABSItemChest::AABSItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	LidMesh->SetRelativeLocation(FVector(-35.0f, 0.0f, 50.0f));
	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	TargetPitch = 110;
}

void AABSItemChest::BeginPlay()
{
	Super::BeginPlay();

	BindWithComponent();

	if(InteractionComp->ActiveGameplayTags.HasTagExact(FGameplayTag::RequestGameplayTag("Interaction.Activated")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Activated Opened");
		StartInteract();
	}
}

void AABSItemChest::BindWithComponent()
{
	InteractionComp->OnInteractedWith.AddDynamic(this, &AABSItemChest::OnInteraction);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "Binding Component");
}

void AABSItemChest::OnInteraction(AActor* InstigatingActor)
{
	UE_LOG(LogTemp, Log, TEXT("AABSItemChest::OnInteraction fired"))
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Interaction Found OnInteraction Triggered");
	
	//If its open close it and remove tag
	if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Interaction.Activated")))
	{
		InteractionComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("Interaction.Activated"));
		EndInteract();
	}
	//If its secured check if player has the proper key to open it
	else if(InteractionComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Interaction.Secure")))
	{
		//
		//
		StartInteract();
		//	
		//	
		//		
	}
	else
	{
		InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("Interaction.Activated"));
		StartInteract();
	}
}

void AABSItemChest::StartInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionStart(this, MyPawn);
}

void AABSItemChest::EndInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IABSGameplayInterface::Execute_InteractionEnd(this, MyPawn);
}

UABSInteractionComponent* AABSItemChest::GetOwningComponent() const
{
	return InteractionComp;
}

void AABSItemChest::OnInteractedWithCallback(AActor* FocusedActor)
{
	UE_LOG(LogTemp, Log, TEXT("On Interacted With Callback on %s"), *GetHumanReadableName())
}