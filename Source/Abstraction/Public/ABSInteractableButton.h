// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableButton.generated.h"

class UABSInteractionComponent;

UCLASS()
class ABSTRACTION_API AABSInteractableButton : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AABSInteractableButton();
	
	UPROPERTY(BlueprintReadWrite, Meta =(InstanceEditable="true"))
	float DepressDepth;

	UFUNCTION()
	void OnInteraction(AActor* InstigatingActor);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartInteract();

	UFUNCTION(BlueprintCallable)
	void EndInteract();
 
	void BindWithComponent();

	void OnInteractedWithCallback(AActor* FocusedActor);

	UPROPERTY(VisibleAnywhere, meta = (InstanceEditable = "true"))
	UABSInteractionComponent* InteractionComp;

	UABSInteractionComponent* GetOwningComponent() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;
};