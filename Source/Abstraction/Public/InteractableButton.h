// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableButton.generated.h"

class UInteractionComponent;

UCLASS()
class ABSTRACTION_API AInteractableButton : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AInteractableButton();

protected:
	UPROPERTY(EditAnywhere, NoClear);
	UInteractionComponent* InteractionComponent;
};
