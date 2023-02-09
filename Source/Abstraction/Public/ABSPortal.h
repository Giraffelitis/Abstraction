// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABSPortal.generated.h"

class UBoxComponent;
class UABSPortalHelper;
class UABSPortalManager;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()
class ABSTRACTION_API AABSPortal : public AActor
{
	GENERATED_BODY()

public:
	AABSPortal();
	
	//Status of the Portal (being visualized by the player or not)
	UFUNCTION(BlueprintPure, Category="Portal")
	bool IsActive() {return bIsActive; }

	UFUNCTION(BlueprintCallable, Category="Portal")
	void SetActive( bool NewActive ) { bIsActive = NewActive; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetRTT(UTexture* RenderTexture);
	
	//Target of where the portal is looking
	UFUNCTION(BlueprintPure, Category="Portal")
	AABSPortal* GetTarget() { return Target; }

	UFUNCTION(BlueprintCallable, Category="Portal")
	void SetTarget(AABSPortal* NewTarget) { Target = NewTarget; }

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void FrontBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void FrontBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void MeshOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void MeshOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category="Portal")
	bool IsPointCrossingPortal( FVector Point);

	UFUNCTION(BlueprintCallable, Category="Portal")
	void TeleportActor( AActor* ActorToTeleport );

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* FrontBoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BackBoxComponent;

	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(EditAnywhere)
	UTextureRenderTarget2D* PortalTexture;
	
	UPROPERTY(BlueprintReadWrite)
	UABSPortalHelper* PortalHelper;

	UPROPERTY(EditAnywhere)
	AABSPortal* Target;
		
protected:
	
	void ConstructSceneCapture();
	void GeneratePortalTexture();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneCaptureAttachPoint; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(BlueprintReadWrite)
	UABSPortalManager* PortalManager;
	
private:
	
	void CheckForTeleport();
	
	bool bIsActive;

	UPROPERTY()
	AActor* TriggeringActor;

	UPROPERTY()
	TEnumAsByte<ECollisionChannel> StoredCollisionChannel;
	
	//Used for Tracking movement of a point
	FVector LastPosition;

	bool bIsCrossing;
	bool bWasInFront;
	bool bIsBehind;
	bool bIsOverlapped;
	bool bIsNearPortal;
};

