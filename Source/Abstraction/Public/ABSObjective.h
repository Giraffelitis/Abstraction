// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "ABSObjective.generated.h"

class UWorld;
class UABSObjectiveComponent;

USTRUCT()
struct FABSObjectiveTagRelationship
{

	GENERATED_BODY()

};

UCLASS()
class ABSTRACTION_API UABSObjective : public UObject
{
	GENERATED_BODY()

protected:
	/* Call this Object to add action functionality to actors and other objects */
	UPROPERTY()
	UABSObjectiveComponent* ObjectiveComp;

	/* Tag Container used to get the parent component the actions are attached to */
	UFUNCTION(BlueprintCallable, Category = "Action")
	UABSObjectiveComponent* GetOwningComponent() const;
		
	/* Tag Container used to add Tags to owning actor when activated, and to remove when action stops */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	/* Tag Container used to add Tags to owning actor when activated, and to remove when action stops */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockingTags;
	
public:
	void Initialize(UABSObjectiveComponent* NewObjectiveComp);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartObjective(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopObjective(AActor* Instigator);
};
