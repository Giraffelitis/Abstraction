// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSGameplayTags.h"
#include "GameplayTagsManager.h"

FABSGameplayTags FABSGameplayTags::GameplayTags;

void FABSGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}
//Add Tags for the editor here.
//AddTag(TagFName, "TagHierarchyName", "TagDescription");
//@TagFName is used on C++ side to assign bindings
//@TagHierarchyName is used on editor side to identify tag and build Hierarchy
//@TagDescription is used by editor to help define tag further if needed

// Changes made here require engine reboot to update in the editor	

void FABSGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	//InputTags
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Attack_Primary, "InputTag.Attack.Primary", "Primary attack input.");
	AddTag(InputTag_Attack_Secondary, "InputTag.Attack.Secondary", "Secondary attack input.");
	AddTag(InputTag_Interact_Primary, "InputTag.Interact.Primary", "Primary Interact input.");
	AddTag(InputTag_Interact_Secondary, "InputTag.Interact.Secondary", "Secondary Interact input.");
	AddTag(InputTag_Sprint, "InputTag.Sprint", "Sprint input.");
	AddTag(InputTag_Parry, "InputTag.Parry", "Parry input.");

	//InteractionTags
	AddTag(InteractionTag_Activated, "InteractionTag.Activated", "Is object activated");
	AddTag(InteractionTag_Secure, "InteractionTag.Secure", "Is object secured?");
	
	//Objective Tags
	AddTag(ObjectiveTag_Inactive, "ObjectiveTag.Inactive", "Objective Inactive.");
	AddTag(ObjectiveTag_Active, "ObjectiveTag.Active", "Object Active.");
	AddTag(ObjectiveTag_Completed, "ObjectiveTag.Complete", "Objective Complete.");
	AddTag(ObjectiveTag_InProgress, "ObjectiveTag.InProgress", "Objective is in progress.");
	AddTag(ObjectiveTag_ReadyToTurnIn, "ObjectiveTag.ReadyToTurnIn", "Objective is ready to be turned in.");
	
	//Security Tags
	AddTag(SecurityTag_Card_Red, "SecurityTag.Card.Red", "Red Security Card.");
	AddTag(SecurityTag_Card_Green, "SecurityTag.Card.Green", "Green Security Card.");
	AddTag(SecurityTag_Card_Yellow, "SecurityTag.Card.Yellow", "Yellow Security Card.");
	AddTag(SecurityTag_Card_Blue, "SecurityTag.Card.Blue", "Blue Security Card.");
}

void FABSGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}