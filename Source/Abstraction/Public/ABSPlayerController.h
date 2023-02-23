// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABSPlayerController.generated.h"

class UABSPortalManager;

UCLASS()
class ABSTRACTION_API AABSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:	
	FMatrix GetCameraProjectionMatrix();
	
	UABSPortalManager* GetPortalManager() {return PortalManager; }

	UPROPERTY(BlueprintReadOnly)
	UABSPortalManager* PortalManager;
	
protected:
	
	virtual void BeginPlay() override;
};
