// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableButton.generated.h"

class UButtonInteractionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);

UCLASS()
class ABSTRACTION_API AInteractableButton : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AInteractableButton();
	virtual void BeginPlay() override;

	float InteractionTime = 1.0f;

	UPROPERTY(BlueprintAssignable, Category = "Button Interaction")
	FOnButtonPressed OnButtonPressed;

protected:
	UFUNCTION()
	void OnInteractionSuccess();

	UPROPERTY(EditAnywhere, NoClear)
	UButtonInteractionComponent* ButtonInteractionComponent;
};
