// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ItemChest.generated.h"

UCLASS()
class ABSTRACTION_API AItemChest : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	AItemChest();
	
	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void OnInteraction(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bLidOpened;

	UFUNCTION()
	void OnLidOpened();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
};
