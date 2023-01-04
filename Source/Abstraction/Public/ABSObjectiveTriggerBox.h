// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ABSObjectiveTriggerBox.generated.h"

class UABSObjectiveComponent;

UCLASS()
class ABSTRACTION_API AABSObjectiveTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AABSObjectiveTriggerBox();
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UABSObjectiveComponent* ObjectiveComp;
};
