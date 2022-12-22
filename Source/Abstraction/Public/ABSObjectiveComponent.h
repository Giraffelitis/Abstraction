// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ABSObjectiveComponent.generated.h"

class UABSObjectiveData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveStateChanged, const UABSObjectiveComponent*);
DECLARE_MULTICAST_DELEGATE_OneParam(FRegisterObjective, const FName);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSObjectiveComponent : public UActorComponent, public IABSGameplayInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABSObjectiveComponent();

	void OnObjectiveInteract();

	FOnObjectiveStateChanged OnStateChanged;

	FRegisterObjective RegisterID;

	//Add Interaction and Security tags to this container.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ObjectiveTags;

	UFUNCTION(BlueprintCallable)
	void ResetObjective();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UABSObjectiveData* ObjectiveData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bObjectiveGiver = false;
	
	UPROPERTY(EditAnywhere, Category = "Objectives")
	FName ObjectiveID;

private:
	virtual void InitializeComponent() override;
};