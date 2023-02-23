// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractableActor.h"
#include "ABSInteractableSwitch.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableSwitch : public AABSInteractableActor
{
	GENERATED_BODY()
	
public:
	AABSInteractableSwitch();
	
	UPROPERTY(EditAnywhere)
	float SwitchAngle;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SwitchMesh;
};
