// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveSubsystem.h"
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
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UABSObjectiveSubsystem::DisplayObjectiveWidget()
{
	if(ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}
}

void UABSObjectiveSubsystem::AddObjective(const FName ObjectiveID)
{
	size_t PrevSize = ObjectiveFNameList.Num();
	ObjectiveFNameList.AddUnique(ObjectiveID);
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
	TArray<FText> NewObjectiveTextList;
	for (int i = 0; i < ObjectiveFNameList.Num(); i++)
	{
		NewObjectiveTextList.Add(FText::FromName(ObjectiveFNameList[i]));
	}
	ObjectiveListWidget->UpdateList(NewObjectiveTextList);
}
