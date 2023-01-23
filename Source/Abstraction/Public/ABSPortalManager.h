// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABSPortalManager.generated.h"

//Forward declaration
class AABSPlayerController;
class UABSPortalHelper;
class ABSPortal;
class AABSPortalProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewLeftPortalProjectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewRightPortalProjectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewLeftPortalLocation, FTransform, SpawnTM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewRightPortalLocation, FTransform, SpawnTM);

UCLASS()
class ABSTRACTION_API UABSPortalManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UABSPortalManager();

	// Called by a Portal actor when wanting to teleport something
	UFUNCTION(BlueprintCallable, Category="Portal")
	void RequestTeleportByPortal( AABSPortal* Portal, AActor* TargetToTeleport );

	// Save a reference to the PlayerController
	void SetControllerOwner(AABSPlayerController* NewOwner );

	void Init();

	UFUNCTION()
	void SpawnLeftPortal(FTransform SpawnTM);

	UFUNCTION()
	void SpawnRightPortal(FTransform SpawnTM);

	// Manual Tick
	void Update( float DeltaTime );

	// Find all the portals in world and update them
	// returns the most valid/usable one for the Player
	AABSPortal* UpdatePortalsInWorld();

	// Update SceneCapture
	void UpdateCapture(AABSPortal* Portal);

	UPROPERTY()
	AABSPortal* LeftPortal;

	UPROPERTY()
	AABSPortal* RightPortal;

	UPROPERTY()
	AABSPortalProjectile* PortalProjectile;

	UPROPERTY()
	FNewLeftPortalProjectile NewLeftPortalProjectile;

	UPROPERTY()
	FNewRightPortalProjectile NewRightPortalProjectile;
	
	UPROPERTY()
	FNewLeftPortalLocation NewLeftPortalLocation;

	UPROPERTY()
	FNewRightPortalLocation NewRightPortalLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PortalToSpawn;
	
protected:
	virtual void BeginPlay() override;


private:	

	void UpdatePortalTexture();
	
	UPROPERTY()
	UABSPortalHelper* PortalHelper;

	UPROPERTY()
	AABSPlayerController* ControllerOwner;
	
	int32 PreviousScreenSizeX;
	int32 PreviousScreenSizeY;
	float UpdateDelay;
};
