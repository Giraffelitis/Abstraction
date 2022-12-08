// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableElevator.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableElevator : public AABSInteractableActor
{
	GENERATED_BODY()

public:
	AABSInteractableElevator();

	UPROPERTY(BlueprintReadWrite, meta = (InstanceEditable="true"))
	float LiftHeight;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BackRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LeftRailingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RightRailingMesh;
};