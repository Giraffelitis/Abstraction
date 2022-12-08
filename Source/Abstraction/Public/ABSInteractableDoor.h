// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableDoor.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableDoor : public AABSInteractableActor
{
	GENERATED_BODY()
	
public:
	AABSInteractableDoor();
	
	UPROPERTY(BlueprintReadWrite, meta = (InstanceEditable="true"))
	float TargetOpenAngle;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;

};
