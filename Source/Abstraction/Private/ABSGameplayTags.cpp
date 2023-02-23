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
	AddTag(InteractionTag_State_Activated, "InteractionTag.State.Activated", "Object is activated");
	AddTag(InteractionTag_State_Available,"InteractionTag.State.Available", "Object is available for use");
	AddTag(InteractionTag_State_Blocked,"InteractionTag.State.Blocked", "Object is blocked from being used");
	AddTag(InteractionTag_State_Unknown,"InteractionTag.State.Unknown", "Object Status Unknown");
	AddTag(InteractionTag_State_Collectible,"InteractionTag.State.Collectible", "Object can be collected");
	
	//Objective Tags
	AddTag(ObjectiveTag_Class_MainStory, "ObjectiveTag.Class.MainStory", "Main Story Mission");
	AddTag(ObjectiveTag_Class_SideMission, "ObjectiveTag.Class.SideMission", "Side Mission");
	AddTag(ObjectiveTag_Class_Repeatable, "ObjectiveTag.Class.Repeatable", "Repeatable Mission");
	
	AddTag(ObjectiveTag_State_Failed, "ObjectiveTag.State.Failed", "Objective Failed");
	AddTag(ObjectiveTag_State_NotAvailableYet, "ObjectiveTag.State.NotAvailableYet", "Objective Not Yet Available");
	AddTag(ObjectiveTag_State_Available, "ObjectiveTag.State.Available", "Objective Available");
	AddTag(ObjectiveTag_State_Completed, "ObjectiveTag.State.Completed", "Objective Complete.");
	AddTag(ObjectiveTag_State_InProgress, "ObjectiveTag.State.InProgress", "Objective is in progress.");
	AddTag(ObjectiveTag_State_ReadyToTurnIn, "ObjectiveTag.State.ReadyToTurnIn", "Objective is ready to be turned in.");

	AddTag(ObjectiveTag_Type_Interact, "ObjectiveTag.Type.Interact", "Objective to Interact with object or actor");
	AddTag(ObjectiveTag_Type_Collect, "ObjectiveTag.Type.Collect", "Objective to collect objects or actors");
	AddTag(ObjectiveTag_Type_Defeat, "ObjectiveTag.Type.Defeat", "Objective to defeat actor(s)");
	AddTag(ObjectiveTag_Type_Travel, "ObjectiveTag.Type.Travel", "Objective to travel to location");	
	
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