// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSItemChest.h"
#include "ABSAction.h"
#include "ABSInteractionTagsComponent.h"
#include "Components/StaticMeshComponent.h"

AABSItemChest::AABSItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	LidMesh->SetRelativeLocation(FVector(-35.0f, 0.0f, 50.0f));
	InteractionTagsComp = CreateDefaultSubobject<UABSInteractionTagsComponent>(TEXT("InteractionTag Component"));
	TargetPitch = 110;
}

void AABSItemChest::BeginPlay()
{
	Super::BeginPlay();

	if(InteractionTagsComp->ActiveGameplayTags.HasTagExact(FGameplayTag::RequestGameplayTag("Interaction.Activated")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Activated Opened");
		OnLidOpened();
	}
}

void AABSItemChest::OnInteraction(AActor* Instigator)
{
	//If its open close it and remove tag
	if(InteractionTagsComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Interaction.Activated")))
	{
		InteractionTagsComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("Interaction.Activated"));
		OnLidOpened();
	}
	//If its secured check if player has the proper key to open it
	else if(InteractionTagsComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Interaction.Secure")))
	{
		//
		//
		//	
		//	
		//	
		//		
	}
	else
	{
		InteractionTagsComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("Interaction.Activated"));
		OnLidOpened();
	}
}

void AABSItemChest::OnLidOpened()
{
	float CurrPitch = 110.0f;/*bLidOpened ? TargetPitch : 0.0f;*/
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}
