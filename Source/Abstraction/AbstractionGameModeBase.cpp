// Copyright Epic Games, Inc. All Rights Reserved.


#include "AbstractionGameModeBase.h"
#include "ABSObjectiveSubsystem.h"

void AAbstractionGameModeBase::StartPlay()
{
	Super::StartPlay();

	UABSObjectiveSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UABSObjectiveSubsystem>();
	if(ObjectiveSubsystem)
	{
		ObjectiveSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveSubsystem->DisplayObjectiveWidget();
	}
}

