// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ABSItemChest.generated.h"

UCLASS()
class ABSTRACTION_API AABSItemChest : public AABSInteractableActor
{
	GENERATED_BODY()

public:
	AABSItemChest();

protected:
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

};
