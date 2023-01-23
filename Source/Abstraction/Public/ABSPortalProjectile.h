// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABSPortalProjectile.generated.h"

class UABSPortalManager;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class AABSPortal;

UCLASS()
class ABSTRACTION_API AABSPortalProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABSPortalProjectile();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PortalBP;

protected:
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY()
	AABSPortal* SpawnedPortal;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetAsLeftPortal();

	UFUNCTION()
	void SetAsRightPortal();

	virtual void SpawnPortal(AABSPortal* SpawnedActor) {};

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsLeftPortalProjectile;

	UPROPERTY()
	UABSPortalManager* PM;

};
