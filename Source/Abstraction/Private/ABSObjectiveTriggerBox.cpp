// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSObjectiveTriggerBox.h"
#include "ABSObjectiveComponent.h"

AABSObjectiveTriggerBox::AABSObjectiveTriggerBox()
{
//	OnActorBeginOverlap.AddDynamic(this, &AABSObjectiveTriggerBox::OnOverlapBegin);
//	OnActorEndOverlap.AddDynamic(this, &AABSObjectiveTriggerBox::OnOverlapEnd);
	
	ObjectiveComp = CreateDefaultSubobject<UABSObjectiveComponent>(TEXT("Objective Component"));
}

void AABSObjectiveTriggerBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr and that 
	if (OtherActor && (OtherActor != this))
	{
		
	}
}

void AABSObjectiveTriggerBox::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		
	}
}