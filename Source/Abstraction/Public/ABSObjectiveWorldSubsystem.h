
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ABSObjectiveComponent.h"
#include "ABSGameplayTags.h"
#include "ABSObjective.h"
#include "ABSObjectiveWorldSubsystem.generated.h"


class UABSObjectiveComponent;
class UABSObjectivesWidget;
class UUserWidget;

UCLASS()
class ABSTRACTION_API UABSObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	UABSObjectiveWorldSubsystem() {}

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription(UABSObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void AddObjective(UABSObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UABSObjectiveComponent* ObjectiveComponent);
	
	//we call this from maps that we want to display objectives(ie main menu will not call this function)
	UFUNCTION(BlueprintCallable)
	void OnMapStart();
	
protected:

	virtual void Deinitialize() override;

	void CreateObjectiveWidgets();

	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompleteWidget();
	void RemoveObjectivesCompleteWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent);
private:

	UPROPERTY()
	UABSObjectivesWidget*	ObjectiveWidget = nullptr;
	
	UPROPERTY()
	UUserWidget*	ObjectivesCompleteWidget = nullptr;

	TArray<const UABSObjectiveComponent*> Objectives;
};