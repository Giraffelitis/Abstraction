// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableElevator.generated.h"

class UABSInteractionComponent;

UCLASS()
class ABSTRACTION_API AABSInteractableElevator : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	AABSInteractableElevator();

	UPROPERTY(BlueprintReadWrite)
	float LiftHeight;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly)
	bool bElevatorActivated;

	UFUNCTION()
	void OnElevatorActivated();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BackRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LeftRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RightRailingMesh;
};