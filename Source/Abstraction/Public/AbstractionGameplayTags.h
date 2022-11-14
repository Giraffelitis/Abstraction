// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 *	GameplayTags
 *	Singleton containing native gameplay tags.
 */

struct FAbstractionGameplayTags
{
public:

	static const FAbstractionGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	//Add Input Tags here the .cpp side adds them to the Editor side 
	//InputTags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Fire;
	FGameplayTag InputTag_Interact;

	//ObjectiveTags
	FGameplayTag Objective_Inactive;
	FGameplayTag Objective_Active;
	FGameplayTag Objective_Complete;
	
protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FAbstractionGameplayTags GameplayTags;
};