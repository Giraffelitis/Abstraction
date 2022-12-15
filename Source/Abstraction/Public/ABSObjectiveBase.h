// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "ABSObjectiveBase.generated.h"

USTRUCT(BlueprintType, Category = Objective)
struct FObjectiveInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	TMap<FString, FString> ObjectiveData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FText ObjectiveText;
	
};

USTRUCT(BlueprintType, Category = Objective)
struct FObjectiveRewards : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	float Experience;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	float Currency;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	float Reputation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	TMap<FName, int> GuaranteedItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	TMap<FName, int> RandomizedItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	TMap<FName, int> UserSelectedItems;
	
};


USTRUCT(BlueprintType, Category = Objective)
struct FObjective : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FGameplayTag ObjectiveType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FString LevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FObjectiveRewards Rewards;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	TArray<FObjectiveInfo> ObjectiveInfo;

};

USTRUCT(BlueprintType, Category = Objective)
struct FObjectiveDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Objectives)
	FObjective Objective;
};


UCLASS()
class ABSTRACTION_API UABSObjectiveBase : public UObject
{
	GENERATED_BODY()

	UABSObjectiveBase();

public:

	UFUNCTION(BlueprintCallable)
	void SetObjectiveDetails(FString name, FString description);
	
	UFUNCTION(BlueprintCallable)
	void SetupObjective(int objectiveNUm, FString description, int numRequired);
	
	UFUNCTION(BlueprintCallable)
	void SetNumObjectives(int numObjectives);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjectiveInfo ObjectiveInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjectiveRewards Rewards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjective Objective;

};
