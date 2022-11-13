// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"

UCLASS()
class ABSTRACTION_API AInteractableDoor : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AInteractableDoor();
	
	UPROPERTY(EditAnywhere)
	float TargetOpenAngle;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bDoorOpened;

	UFUNCTION()
	void OnDoorOpened();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;
};
