// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableDoor.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableDoor : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AABSInteractableDoor();
	
	void OnInteraction(APawn* InstigatorPawn);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (InstanceEditable="true"))
	float TargetOpenAngle;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	bool IsSecured;
	
	UPROPERTY(BlueprintReadOnly)
	bool bDoorOpened;

	UFUNCTION()
	void OnDoorOpened();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;
};
