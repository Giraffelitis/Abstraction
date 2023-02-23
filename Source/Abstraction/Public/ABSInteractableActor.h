// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableActor.generated.h"

class UABSInteractionComponent;

UCLASS()
class ABSTRACTION_API AABSInteractableActor : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABSInteractableActor();

	UFUNCTION()
	void OnInteraction(AActor* InstigatingActor);


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, meta = (InstanceEditable = "true"))
	UABSInteractionComponent* InteractionComp;
 
	void BindWithComponent();

	void OnInteractedWithCallback(AActor* FocusedActor);

	UABSInteractionComponent* GetOwningComponent() const;

};
