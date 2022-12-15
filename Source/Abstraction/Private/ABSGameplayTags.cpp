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
	AddTag(ObjectiveTag_Type_MainStory, "ObjectiveTag.Type.MainStory", "Main Story Mission");
	AddTag(ObjectiveTag_Type_SideMission, "ObjectiveTag.Type.SideMission", "Side Mission");
	AddTag(ObjectiveTag_Type_Repeatable, "ObjectiveTag.Type.Repeatable", "Repeatable Mission");
	
	AddTag(ObjectiveTag_State_Failed, "ObjectiveTag.State.Failed", "Objective Failed");
	AddTag(ObjectiveTag_State_NotAvailableYet, "ObjectiveTag.State.NotAvailableYet", "Objective Not Yet Available");
	AddTag(ObjectiveTag_State_Available, "ObjectiveTag.State.Available", "Objective Available");
	AddTag(ObjectiveTag_State_Completed, "ObjectiveTag.State.Complete", "Objective Complete.");
	AddTag(ObjectiveTag_State_InProgress, "ObjectiveTag.State.InProgress", "Objective is in progress.");
	AddTag(ObjectiveTag_State_ReadyToTurnIn, "ObjectiveTag.State.ReadyToTurnIn", "Objective is ready to be turned in.");

	AddTag( ObjectiveTag_Interact_Activate, "ObjectiveTag.Interact.Activate", "Objective to Activate Object");
	AddTag( ObjectiveTag_Interact_Deactivate, "ObjectiveTag.Interact.Deactivate", "Objective to Deactivate Object");
	AddTag( ObjectiveTag_Interact_Pickup, "ObjectiveTag.Interact.Pickup", "Objective to Pickup Object");
	AddTag( ObjectiveTag_Interact_Deliver, "ObjectiveTag.Interact.Deliver", "Objective to Deliver Object");
	AddTag( ObjectiveTag_Interact_Heal, "ObjectiveTag.Interact.Heal", "Objective to Heal Object");
	AddTag( ObjectiveTag_Interact_Destroy, "ObjectiveTag.Interact.Destroy", "Objective to Kill or Destroy Object");
	
	AddTag( ObjectiveTag_Location_Enter, "ObjectiveTag.Location.Enter", "Objective to Enter an area");
	AddTag( ObjectiveTag_Location_Exit, "ObjectiveTag.Location.Exit", "Objective to exit an area");
	
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