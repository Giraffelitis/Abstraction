// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"

class UObjectiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectiveComponent();

	UFUNCTION(BlueprintCallable)
	const FString& GetDescription() const { return Description; }
	
	void SetState();
	
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitializeComponent() override;

	UPROPERTY(EditAnywhere)
	FString Description;
};
