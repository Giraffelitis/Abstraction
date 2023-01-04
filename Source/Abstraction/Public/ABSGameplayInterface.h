// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABSGameplayInterface.generated.h"


//	This class does not need to be modified.
//	There is no .cpp file associated with this header
UINTERFACE()
class UABSGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

class ABSTRACTION_API IABSGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractionStart(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractionEnd(APawn* InstigatorPawn);
};
