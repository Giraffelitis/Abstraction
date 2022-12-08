// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "../AbstractionGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ABSObjectivesWidget.h"
#include "ABSObjectiveComponent.h"
#include "NativeGameplayTags.h"

FString UABSObjectiveWorldSubsystem::GetCurrentObjectiveDescription(UABSObjectiveComponent* ObjectiveComponent)
{
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Inactive")))
		{
			return TEXT("N/A");
		}

		FString RetObjective = "Objectives[0]->GetDescription()";
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Completed")))
		{
			RetObjective += TEXT(" Completed!");
		}
		return RetObjective;
}

void UABSObjectiveWorldSubsystem::AddObjective(UABSObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	if(ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag")))
	{		
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "ObjectiveTagFound");
		Objectives.AddUnique(ObjectiveComponent);
		if (Objectives.Num() > PrevSize)
		{
			ObjectiveComponent->OnStateChanged.AddUObject(this, &UABSObjectiveWorldSubsystem::OnObjectiveStateChanged);
		}
	}
}

void UABSObjectiveWorldSubsystem::RemoveObjective(UABSObjectiveComponent* ObjectiveComponent)
{
	int32 numRemoved = ObjectiveComponent->OnStateChanged.RemoveAll(this);
	check(numRemoved);
	Objectives.Remove(ObjectiveComponent);
}

void UABSObjectiveWorldSubsystem::OnMapStart()
{
	AAbstractionGameModeBase* GameMode = Cast<AAbstractionGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CreateObjectiveWidgets();
		DisplayObjectiveWidget();
	}
}

void UABSObjectiveWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();

	ObjectiveWidget = nullptr;
	ObjectivesCompleteWidget = nullptr;
}

void UABSObjectiveWorldSubsystem::CreateObjectiveWidgets()
{
	if (ObjectiveWidget == nullptr)
	{
		AAbstractionGameModeBase* GameMode = Cast<AAbstractionGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ObjectiveWidget = CreateWidget<UABSObjectivesWidget>(PlayerController, GameMode->ObjectiveWidgetClass);
			ObjectivesCompleteWidget = CreateWidget<UUserWidget>(PlayerController, GameMode->ObjectivesCompleteWidgetClass);
		}
	}
}

void UABSObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		if (!ObjectiveWidget->IsInViewport())
		{
			ObjectiveWidget->AddToViewport();
		}
		
		ObjectiveWidget->UpdateObjectiveText(GetCompletedObjectiveCount(), Objectives.Num());
	}
}

void UABSObjectiveWorldSubsystem::RemoveObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		ObjectiveWidget->RemoveFromParent();
	}
}

void UABSObjectiveWorldSubsystem::DisplayObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->AddToViewport();
	}
}

void UABSObjectiveWorldSubsystem::RemoveObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->RemoveFromParent();
	}
}

uint32 UABSObjectiveWorldSubsystem::GetCompletedObjectiveCount()
{
	uint32 ObjectivedCompleted = 0u;
	for (const UABSObjectiveComponent* OC : Objectives)
	{
		if (OC && OC->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Completed")))
		{
			++ObjectivedCompleted;
		}
	}

	return ObjectivedCompleted;
}


void UABSObjectiveWorldSubsystem::OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent)
{

	//ADD IN DIFFERENT SITUATIONS FOR STATE CHANGES
	
	if (Objectives.Num() == 0 || !Objectives.Contains(ObjectiveComponent))
	{
		return;
	}

	//check if game is over... 
	if (ObjectiveWidget && ObjectivesCompleteWidget)
	{
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("ObjectiveTag.Completed")) && GetCompletedObjectiveCount() == Objectives.Num())
		{
			//GameOver
			DisplayObjectivesCompleteWidget();
		}
		else
		{
			DisplayObjectiveWidget();
		}
	}
}