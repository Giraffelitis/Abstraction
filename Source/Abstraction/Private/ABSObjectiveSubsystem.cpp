// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveSubsystem.h"

#include "ABSObjectiveComponent.h"
#include "ABSObjectiveData.h"
#include "ABSObjectiveListWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UABSObjectiveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);	
}

void UABSObjectiveSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if(ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if(PlayerController)
			ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UABSObjectiveSubsystem::DisplayObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		if (!ObjectiveWidget->IsInViewport())
		{
			ObjectiveWidget->AddToViewport();
		}
	}
}

void UABSObjectiveSubsystem::RemoveObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		if (ObjectiveWidget->IsInViewport())
		{
			ObjectiveWidget->RemoveFromParent();
		}
	}
}

void UABSObjectiveSubsystem::AddObjective(UABSObjectiveComponent* ObjectiveComponent, UABSObjectiveData* ObjData)
{
	size_t PrevSize = ObjectiveDataList.Num();
	ObjectiveDataList.AddUnique(ObjData);
	if (ObjectiveDataList.Num() > PrevSize)
	{
		ObjectiveComponent->OnStateChanged.AddUObject(this, &UABSObjectiveSubsystem::OnObjectiveStateChanged);
	}
}

void UABSObjectiveSubsystem::OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent)
{
	DisplayObjectiveWidget();
}

FObjectiveData UABSObjectiveSubsystem::FindObjective_Implementation(FName ObjectiveID, bool& Success)
{
	Success = false;

	FObjectiveData ObjectiveData;
	if (ObjectiveDatabase == nullptr) { return ObjectiveData; }
	
	if (ObjectiveDatabase->ObjectiveData.ObjectiveID == ObjectiveID)
	{
		Success = true;
		return ObjectiveDatabase->ObjectiveData;
	}
	
	return ObjectiveData;
}

void UABSObjectiveSubsystem::UpdateObjectiveList_Implementation()
{
	for (int i = 0; i < ObjectiveDataList.Num(); i++)
	{
		if (ObjectiveDataList[i]->ObjectiveData.ObjectiveState == FGameplayTag::RequestGameplayTag("ObjectiveTag.State.InProgress"))
		{
			NewObjectiveList.AddUnique(ObjectiveDataList[i]);
		}
	}
	
	UABSObjectiveListWidget* ObjectiveListWidget = Cast<UABSObjectiveListWidget>(ObjectiveWidget);
	if(ObjectiveListWidget)
		ObjectiveListWidget->UpdateList(NewObjectiveList); 

	DisplayObjectiveWidget();
}
