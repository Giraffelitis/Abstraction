// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FAbstractionGameplayTags FAbstractionGameplayTags::GameplayTags;

void FAbstractionGameplayTags::InitializeNativeTags()
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
void FAbstractionGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	//InputTags
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Fire, "InputTag.Fire", "Fire input.");
	AddTag(InputTag_Interact, "InputTag.Interact", "Interact input.");

	//Objective Tags
	AddTag(Objective_Inactive, "ObjectiveTag.Inactive", "Objective Inactive.");
	AddTag(Objective_Active, "ObjectiveTag.Active", "Object Active.");
	AddTag(Objective_Complete, "ObjectiveTag.Complete", "Objective Complete.");
}

void FAbstractionGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}