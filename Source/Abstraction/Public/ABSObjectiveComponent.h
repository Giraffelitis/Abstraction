// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ABSObjectiveComponent.generated.h"

class UABSObjectiveData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveStateChanged, const UABSObjectiveComponent*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSObjectiveComponent : public UActorComponent, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	
	UABSObjectiveComponent();

	void OnObjectiveInteractWith();

	FOnObjectiveStateChanged OnStateChanged;

	UFUNCTION(BlueprintCallable)
	void ResetObjective();
	FGameplayTag GetObjectiveState();

protected:

	void OnObjectiveUpdate();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UABSObjectiveData* ObjectiveData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bObjectiveGiver = false;

private:
	virtual void InitializeComponent() override;

	FGameplayTag ObjectiveStateTag;
};