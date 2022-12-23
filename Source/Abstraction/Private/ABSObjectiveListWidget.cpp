// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveListWidget.h"
#include "ABSObjectiveData.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScaleBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UABSObjectiveListWidget::UpdateList(TArray<UABSObjectiveData*> UpdatedObjective)
{
	if( ObjectiveListVerticalBox->GetChildrenCount() > 0)
	{
		ObjectiveListVerticalBox->ClearChildren();
	}
	
	for(int i = 0; i < UpdatedObjective.Num(); i++)
	{
		ObjectiveListText = UpdatedObjective[i]->ObjectiveData.Message;
		ObjectiveListBool = (UpdatedObjective[i]->ObjectiveData.ObjectiveState == (FGameplayTag::RequestGameplayTag("ObjectiveTag.State.Completed")));
			
		UHorizontalBox* HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>();
		ObjectiveListVerticalBox->AddChildToVerticalBox(HorizontalBox);

		UScaleBox* ScaleBox = WidgetTree->ConstructWidget<UScaleBox>();
		HorizontalBox->AddChildToHorizontalBox(ScaleBox);
		ScaleBox->SetRenderScale(FVector2d(1.5f, 1.5f));
		
		UCheckBox* CheckBox = WidgetTree->ConstructWidget<UCheckBox>();
		ScaleBox->AddChild(CheckBox);
		CheckBox->SetIsChecked(ObjectiveListBool);
				
		UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>();
		HorizontalBox->AddChildToHorizontalBox(TextBlock);
		TextBlock->SetText(FText(ObjectiveListText));
	}
}
