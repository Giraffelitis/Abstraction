// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ABSKey.generated.h"

class USphereComponent;

UCLASS()
class ABSTRACTION_API AABSKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABSKey();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;
	
	UPROPERTY()
	float DriftAmount;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFloatingUp;

	UPROPERTY(BlueprintReadOnly)
	FVector StartingLocation;

	UPROPERTY(BlueprintReadOnly)
	FVector MaxPosOffset;

	UPROPERTY(BlueprintReadOnly)
	FVector MaxNegOffset;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
