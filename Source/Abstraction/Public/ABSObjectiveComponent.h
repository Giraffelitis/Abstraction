// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABSGameplayTags.h"
#include "ABSObjectiveComponent.generated.h"

class UABSObjectiveComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveStateChanged, const UABSObjectiveComponent*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABSObjectiveComponent();

	UFUNCTION(BlueprintCallable)
	const FString& GetDescription() const { return Description; }

	FOnObjectiveStateChanged OnStateChanged;

	//Add Interaction and Security tags to this container.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ObjectiveTags;

	void UpdateObjectiveTag();
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitializeComponent() override;

	UPROPERTY(EditAnywhere)
	FString Description;

};