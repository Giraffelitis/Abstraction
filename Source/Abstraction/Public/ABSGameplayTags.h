// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 *	GameplayTags
 *	Singleton containing native gameplay tags.
 */

struct FABSGameplayTags
{
public:

	static const FABSGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	//Add Input Tags here the .cpp side adds them to the Editor side 
	//InputTags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Attack_Primary;
	FGameplayTag InputTag_Attack_Secondary;
	FGameplayTag InputTag_Interact_Primary;
	FGameplayTag InputTag_Interact_Secondary;
	FGameplayTag InputTag_Sprint;
	FGameplayTag InputTag_Parry;
	

	//ObjectiveTags
	FGameplayTag Objective_Inactive;		// Not Currently Available
	FGameplayTag Objective_Active;			// Available to Pickup
	FGameplayTag Objective_InProgress;		// Currently in Progress
	FGameplayTag Objective_ReadyToTurnIn;	// All requirements complete and ready to turn in
	FGameplayTag Objective_Complete;		// Completed
	

	//SecurityTag
	FGameplayTag Security_Card_Red;
	FGameplayTag Security_Card_Green;
	FGameplayTag Security_Card_Yellow;
	FGameplayTag Security_Card_Blue;
	
protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FABSGameplayTags GameplayTags;
};