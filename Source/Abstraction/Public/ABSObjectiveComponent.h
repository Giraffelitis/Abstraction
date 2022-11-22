// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ABSObjectiveComponent.generated.h"

class UABSObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveStarted, UABSObjectiveComponent*, OwningComp, UABSObjective*, Objective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveCompleted, UABSObjectiveComponent*, OwningComp, UABSObjective*, Objective);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABSObjectiveComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ObjectiveTags;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveStarted OnObjectiveStarted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveCompleted OnObjectiveCompleted;

	// Not currently used but might be needed for timed objectives?
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
};
/*	Need to create Objective class that will house functions that will add and remove tags through
 *	the different stages and scenarios involving objectives. reference action.cpp
 */
