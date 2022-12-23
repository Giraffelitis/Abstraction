// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ABSObjectiveSubsystem.generated.h"

class UABSObjectiveComponent;
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
	void RemoveObjectiveWidget();

	void AddObjective(UABSObjectiveComponent* ObjectiveComponent, UABSObjectiveData* ObjData);

	void OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Objective")
	FObjectiveData FindObjective(FName ObjectiveID, bool& Success);

	FObjectiveData FindObjective_Implementation(FName ObjectiveID, bool& Success);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective")
	UABSObjectiveData* ObjectiveDatabase;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Objective")
	void UpdateObjectiveList(); 

private:
	
	TArray<UABSObjectiveData*> ObjectiveDataList;
	TArray<UABSObjectiveData*> NewObjectiveList;
	TArray<bool> NewObjectiveListBool;
	
	UUserWidget* ObjectiveWidget = nullptr;
	
	
};
