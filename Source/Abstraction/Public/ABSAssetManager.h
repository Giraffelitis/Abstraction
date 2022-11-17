#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ABSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABSTRACTION_API UABSAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UABSAssetManager();

	// Returns the AssetManager singleton object.
	static UABSAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};