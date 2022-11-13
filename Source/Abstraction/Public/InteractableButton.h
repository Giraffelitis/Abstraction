// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableButton.generated.h"

UCLASS()
class ABSTRACTION_API AInteractableButton : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AInteractableButton();
	
	UPROPERTY(EditAnywhere)
	float DepressDepth;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bButtonPressed;

	UFUNCTION()
	void OnButtonPressed();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;
};