// Fill out your copyright notice in the Description page of Project Settings.

#include "AbstractionAssetManager.h"
#include "AbstractionGameplayTags.h"

UAbstractionAssetManager::UAbstractionAssetManager()
{

}

UAbstractionAssetManager& UAbstractionAssetManager::Get()
{
	check(GEngine);

	UAbstractionAssetManager* AbstractionAssetManager = Cast<UAbstractionAssetManager>(GEngine->AssetManager);
	return *AbstractionAssetManager;
}

void UAbstractionAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FAbstractionGameplayTags::InitializeNativeTags();
}