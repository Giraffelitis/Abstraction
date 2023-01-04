 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABSObjectiveListWidget.generated.h"

class UABSObjectiveData;
class UVerticalBox;
class UTextBlock;
class UABSObjectiveComponent;

UCLASS()
class ABSTRACTION_API UABSObjectiveListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void UpdateList(TArray<UABSObjectiveData*> UpdatedObjective);

protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	FText ObjectiveListText;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	bool ObjectiveListBool;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* ObjectiveListVerticalBox;
};