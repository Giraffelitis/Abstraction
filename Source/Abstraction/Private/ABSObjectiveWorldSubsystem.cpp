// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveWorldSubsystem.h"
#include "ABSGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "../AbstractionGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ABSObjectivesWidget.h"
#include "NativeGameplayTags.h"

FString UABSObjectiveWorldSubsystem::GetCurrentObjectiveDescription(UABSObjectiveComponent* ObjectiveComponent)
{
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("Objective.Inactive")))
		{
			return TEXT("N/A");
		}

		FString RetObjective = "Objectives[0]->GetDescription()";
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("Objective.Completed")))
		{
			RetObjective += TEXT(" Completed!");
		}
		return RetObjective;
}

void UABSObjectiveWorldSubsystem::AddObjective(UABSObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
//		ObjectiveComponent->OnObjectiveStarted.AddDynamic(this, &UABSObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UABSObjectiveWorldSubsystem::RemoveObjective(UABSObjectiveComponent* ObjectiveComponent)
{
	int32 numRemoved = ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("Objective.Completed"));
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
		if (OC && OC->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("Objective.Completed")))
		{
			++ObjectivedCompleted;
		}
	}

	return ObjectivedCompleted;
}


void UABSObjectiveWorldSubsystem::OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent)
{
	if (Objectives.Num() == 0 || !Objectives.Contains(ObjectiveComponent))
	{
		return;
	}

	//check if game is over... 
	if (ObjectiveWidget && ObjectivesCompleteWidget)
	{
		if (ObjectiveComponent->ObjectiveTags.HasTag(FGameplayTag::RequestGameplayTag("Objective.Completed")) && GetCompletedObjectiveCount() == Objectives.Num())
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