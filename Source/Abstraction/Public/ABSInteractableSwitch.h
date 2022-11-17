// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableSwitch.generated.h"

UCLASS()
class ABSTRACTION_API AABSInteractableSwitch : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AABSInteractableSwitch();
	
	UPROPERTY(EditAnywhere)
	float SwitchAngle;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly)
	bool bSwitchedOn;

	UFUNCTION()
	void OnSwitchedOn();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SwitchMesh;
};
