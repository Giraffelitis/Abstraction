// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "ABSObjectiveData.generated.h"

USTRUCT(BlueprintType, Category = Objective)
struct FObjectiveData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FName ObjectiveID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FName ObjectiveGrantor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FText Message;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FText SortDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FText CompletedMessage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FGameplayTag ObjectiveType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FGameplayTag ObjectiveState;	
};

UCLASS()
class ABSTRACTION_API UABSObjectiveData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Objective")
	FObjectiveData ObjectiveData;

};
