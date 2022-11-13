// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AbstractionAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABSTRACTION_API UAbstractionAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UAbstractionAssetManager();

	// Returns the AssetManager singleton object.
	static UAbstractionAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};