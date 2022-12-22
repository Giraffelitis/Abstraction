// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveListWidget.h"
#include "Components/TextBlock.h"

void UABSObjectiveListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Objective0->SetText(FText::FromString(TEXT("Close the Chest")));
	Objective1->SetText(FText::FromString(TEXT("Open The Door")));
	Objective2->SetText(FText::FromString(TEXT("Ride the Elevator")));
	Objective3->SetText(FText::FromString(TEXT("Flip The Switch")));
	Objective4->SetText(FText::FromString(TEXT("")));
}

void UABSObjectiveListWidget::UpdateList(TArray<FText> NewList)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "UABSObjectiveListWidget::UpdateList Called");	
	/*
	 *		It gives a read access violation error here I think it has to do with calling it from the subsystem instead of from a delegate listener? 
	 *
	for (int i = 0; i < ObjectiveTextList.Num(); i++)
	{
		switch (i)
		{
		case 0:
			{Objective0->SetText(FText(ObjectiveTextList[i])); break; }
		case 1:
			{Objective1->SetText(FText(ObjectiveTextList[i])); break; }
		case 2:
			{Objective2->SetText(FText(ObjectiveTextList[i])); break; }
		case 3:
			{Objective3->SetText(FText(ObjectiveTextList[i])); break; }
		case 4:
			{Objective4->SetText(FText(ObjectiveTextList[i])); break; }
		default:
			{}
		}
	}
	*/
}
