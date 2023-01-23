// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSPortalHelper.generated.h"

class UBoxComponent;
class AABSPortalManager;
/**
 * 
 */
UCLASS()
class ABSTRACTION_API UABSPortalHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Portal")
	bool IsPointInsideBox(FVector Point, UBoxComponent* Box);

	FVector ConvertLocationToActorSpace(FVector Location, AActor* Reference, AActor* Target);

	FRotator ConvertRotationToActorSpace(FRotator Rotation, AActor* Reference, AActor* Target);

	UFUNCTION(BlueprintCallable)
	UABSPortalManager* GetPortalManager(AActor* Context);
};
