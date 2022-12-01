// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ABSInteractableDoor.generated.h"

class UABSInteractionComponent;

UCLASS()
class ABSTRACTION_API AABSInteractableDoor : public AActor, public IABSGameplayInterface
{
	GENERATED_BODY()
	
public:
	AABSInteractableDoor();
	
	UPROPERTY(BlueprintReadWrite, meta = (InstanceEditable="true"))
	float TargetOpenAngle;

	UFUNCTION()
	void OnInteraction(AActor* InstigatingActor);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartInteract();

	UFUNCTION(BlueprintCallable)
	void EndInteract();	

	UPROPERTY(VisibleAnywhere, meta = (InstanceEditable = "true"))
	UABSInteractionComponent* InteractionComp;
 
	void BindWithComponent();

	void OnInteractedWithCallback(AActor* FocusedActor);

	UABSInteractionComponent* GetOwningComponent() const;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;
};
