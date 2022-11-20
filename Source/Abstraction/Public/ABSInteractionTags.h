// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "ABSInteractionTags.generated.h"

class UABSInteractionComponent;

UCLASS()
class ABSTRACTION_API UABSInteractionTags : public UObject
{
	GENERATED_BODY()

	/* Call this Object to add action functionality to actors and other objects */
	UPROPERTY()
	UABSInteractionComponent* InteractionComp;

	/* Tag Container used to add Tags to owning actor when activated, and to remove when action stops */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer InteractionTags;

	/* Tag Container used if Action can only start if OwningActor has none of these Tags applied */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer SecurityTags;

	/* Tag Container used to get the parent component the actions are attached to */
	UFUNCTION(BlueprintCallable, Category = "Action")
	UABSInteractionComponent* GetOwningComponent() const;
	
public:

	void Initialize(UABSInteractionComponent* NewInteractionComp);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void StartInteraction(AActor* Instigator);

	/* Action nickname to start/stop without a reference to the object */
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FName ActionName;
};
