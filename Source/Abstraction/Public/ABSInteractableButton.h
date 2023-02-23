// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractableActor.h"
#include "ABSInteractableButton.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableButton : public AABSInteractableActor
{
	GENERATED_BODY()
	
public:
	AABSInteractableButton();
	
	UPROPERTY(BlueprintReadWrite, Meta =(InstanceEditable="true"))
	float DepressDepth;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;
};