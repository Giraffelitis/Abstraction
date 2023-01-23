// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPlayerController.h"

FMatrix AABSPlayerController::GetCameraProjectionMatrix()
{
	FMatrix ProjectionMatrix;

	if( GetLocalPlayer() != nullptr )
	{
		FSceneViewProjectionData PlayerProjectionData;

		GetLocalPlayer()->GetProjectionData(GetLocalPlayer()->ViewportClient->Viewport, PlayerProjectionData);

		ProjectionMatrix = PlayerProjectionData.ProjectionMatrix;
	}

	return ProjectionMatrix;
}

void AABSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	
}

