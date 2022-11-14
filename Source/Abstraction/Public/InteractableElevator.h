// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableElevator.generated.h"


UCLASS()
class ABSTRACTION_API AInteractableElevator : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	AInteractableElevator();

	UPROPERTY(BlueprintReadWrite)
	float LiftHeight;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bButtonPressed;

	UFUNCTION()
	void OnButtonPressed();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BackRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LeftRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RightRailingMesh;
};