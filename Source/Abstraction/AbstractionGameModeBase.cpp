// Copyright Epic Games, Inc. All Rights Reserved.


#include "AbstractionGameModeBase.h"

#include "ABSObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void AAbstractionGameModeBase::StartPlay()
{
	Super::StartPlay();
	//UABSObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UABSObjectiveWorldSubsystem>;
	//if (ObjectiveWorldSubsystem)
	//{
	//	ObjectiveWorldSubsystem->CreateObjectiveWidgets();
	//	ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	//}

}