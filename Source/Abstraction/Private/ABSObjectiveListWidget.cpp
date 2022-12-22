// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveListWidget.h"
#include "Components/TextBlock.h"

void UABSObjectiveListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Objective0->SetText(FText::FromString(TEXT("Open The Door")));
	Objective1->SetText(FText::FromString(TEXT("Ride The Elevator")));
	Objective2->SetText(FText::FromString(TEXT("Open The Chest")));
	Objective3->SetText(FText::FromString(TEXT("Flip The Switch")));
	Objective4->SetText(FText::FromString(TEXT("")));
	
}

void UABSObjectiveListWidget::UpdateList(TArray<FText> NewList)
{
	/*
	 *		Getting an access violation when trying to update the values during gameplay and cannot figure out why. 
	 *
	for (int i = 0; i < NewList.Num(); i++)
	{
		switch (i)
		{
		case 0:
			{Objective0->SetText(FText(NewList[i])); break; }
		case 1:
			{Objective1->SetText(FText(NewList[i])); break; }
		case 2:
			{Objective2->SetText(FText(NewList[i])); break; }
		case 3:
			{Objective3->SetText(FText(NewList[i])); break; }
		case 4:
			{Objective4->SetText(FText(NewList[i])); break; }
		default:
			{}
		}
	}
	*/
}
