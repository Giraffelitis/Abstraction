// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABSObjectiveListWidget.generated.h"

class UTextBlock;
class UABSObjectiveComponent;

UCLASS()
class ABSTRACTION_API UABSObjectiveListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateList(TArray<FText> NewList);

protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Objective0;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Objective1;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Objective2;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Objective3;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Objective4;

	UPROPERTY(BlueprintReadWrite)
	TArray<FText> ObjectiveTextList;
	
private:

	UABSObjectiveComponent* ObjectiveComponent;
};