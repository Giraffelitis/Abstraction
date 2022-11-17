// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableButton.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableButton : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AABSInteractableButton();
	
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