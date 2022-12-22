// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ABSObjectiveSubsystem.generated.h"

class UABSObjectiveData;
class UABSObjectiveListWidget;

UCLASS()
class ABSTRACTION_API UABSObjectiveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	void AddObjective(const FName ObjectiveID);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Objective")
	FObjectiveData FindObjective(FName ObjectiveID, bool& Success);

	FObjectiveData FindObjective_Implementation(FName ObjectiveID, bool& Success);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective")
	UABSObjectiveData* ObjectiveDatabase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective")
	UABSObjectiveListWidget* ObjectiveListWidget;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Objective")
	void UpdateObjectiveList(); 

private:

	TArray<FName> ObjectiveFNameList;
	
	UUserWidget* ObjectiveWidget = nullptr;
	
};
