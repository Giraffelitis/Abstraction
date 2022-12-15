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

	//InteractionTags
	FGameplayTag InteractionTag_Activated;
	FGameplayTag InteractionTag_Secure;

	//ObjectiveTags
	FGameplayTag ObjectiveTag_Type_MainStory;
	FGameplayTag ObjectiveTag_Type_SideMission;
	FGameplayTag ObjectiveTag_Type_Repeatable;

	//ObjectiveTags States
	FGameplayTag ObjectiveTag_State_Failed;				// Not Currently Available
	FGameplayTag ObjectiveTag_State_NotAvailableYet;	// Not Available to pickup yet	
	FGameplayTag ObjectiveTag_State_Available;			// Available to Pickup
	FGameplayTag ObjectiveTag_State_InProgress;			// Currently in Progress
	FGameplayTag ObjectiveTag_State_ReadyToTurnIn;		// All requirements complete and ready to turn in
	FGameplayTag ObjectiveTag_State_Completed;			// Completed

	//ObjectiveTags Types
	FGameplayTag ObjectiveTag_Interact_Activate;
	FGameplayTag ObjectiveTag_Interact_Deactivate;
	FGameplayTag ObjectiveTag_Interact_Pickup;
	FGameplayTag ObjectiveTag_Interact_Deliver;
	FGameplayTag ObjectiveTag_Interact_Heal;
	FGameplayTag ObjectiveTag_Interact_Destroy;
	FGameplayTag ObjectiveTag_Location_Enter;
	FGameplayTag ObjectiveTag_Location_Exit;
	
	//SecurityTag
	FGameplayTag SecurityTag_Card_Red;
	FGameplayTag SecurityTag_Card_Green;
	FGameplayTag SecurityTag_Card_Yellow;
	FGameplayTag SecurityTag_Card_Blue;
	
protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FABSGameplayTags GameplayTags;
};