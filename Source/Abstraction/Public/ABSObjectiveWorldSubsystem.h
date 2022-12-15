
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ABSObjectiveWorldSubsystem.generated.h"

class UABSObjectiveEvents;
class UABSObjectiveHandler;
class UABSObjectiveComponent;
class UABSObjectiveWidget;
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
	
	void CreateObjectiveWidgets();

	void DisplayObjectiveWidget();
	
	void RemoveObjectiveWidget();
		
protected:

	virtual void Deinitialize() override;

	void DisplayObjectivesCompleteWidget();
	
	void RemoveObjectivesCompleteWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(const UABSObjectiveComponent* ObjectiveComponent);
private:

	UPROPERTY()
	UABSObjectiveWidget* ObjectiveWidget = nullptr;

	UPROPERTY()
	UABSObjectiveWidget* ObjectivesCompleteWidget = nullptr;

	TArray<const UABSObjectiveComponent*> Objectives;
};