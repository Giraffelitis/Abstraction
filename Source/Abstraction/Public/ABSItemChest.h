// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSItemChest.generated.h"

class UABSInteractionTagsComponent;

UCLASS()
class ABSTRACTION_API AABSItemChest : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	AABSItemChest();
	
	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void OnInteraction(AActor* Instigator);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void OnLidOpened();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere)
	UABSInteractionTagsComponent* InteractionTagsComp;

};
