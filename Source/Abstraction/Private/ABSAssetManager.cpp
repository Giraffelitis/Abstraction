#include "ABSAssetManager.h"
#include "ABSGameplayTags.h"

UABSAssetManager::UABSAssetManager()
{

}

UABSAssetManager& UABSAssetManager::Get()
{
	check(GEngine);

	UABSAssetManager* MyAssetManager = Cast<UABSAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UABSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FABSGameplayTags::InitializeNativeTags();
}