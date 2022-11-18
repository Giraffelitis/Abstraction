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
	
	UPROPERTY(BlueprintReadWrite, Meta =(InstanceEditable="true"))
	float DepressDepth;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditAnywhere)
	bool bButtonPressed;

	UFUNCTION()
	void OnButtonPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;
};