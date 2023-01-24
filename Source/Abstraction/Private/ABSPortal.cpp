 // Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPortal.h"
#include "ABSPortalHelper.h"
#include "ABSPlayerCharacter.h"
#include "ABSPlayerController.h"
#include "ABSPortalManager.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

 // Sets default values
AABSPortal::AABSPortal()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsActive = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->Mobility = EComponentMobility::Static;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal Mesh"));
	PortalMesh->SetupAttachment(RootComponent);
	
	FrontBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Front Portal Area"));
	FrontBoxComponent->SetupAttachment(RootComponent);

	BackBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Portal Area"));
	BackBoxComponent->SetupAttachment(RootComponent);  

	SceneCaptureAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Portal Render Reference"));
	SceneCaptureAttachPoint->SetupAttachment(RootComponent);
	SceneCaptureAttachPoint->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture"));
	SceneCapture->SetupAttachment(SceneCaptureAttachPoint);

	PortalHelper = CreateDefaultSubobject<UABSPortalHelper>(TEXT("Portal Helper"));

	bIsOverlapped = false;

	ConstructSceneCapture();
}

 void AABSPortal::ClearRTT_Implementation()
 {
 }

 void AABSPortal::SetRTT_Implementation(UTexture* RenderTexture)
 {
 }

void AABSPortal::ConstructSceneCapture()
{
	//------------------------------------------------
	//Create Camera
	//------------------------------------------------
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->LODDistanceFactor = 3; //Force bigger LODs for faster computations
	SceneCapture->TextureTarget = PortalTexture;
	SceneCapture->bEnableClipPlane = true;
	SceneCapture->bUseCustomProjectionMatrix = true;
	SceneCapture->CaptureSource = SCS_SceneColorHDRNoAlpha;

	//Setup Post-Process of SceneCapture (optimization : disable Motion Blur, etc)
	FPostProcessSettings CaptureSettings;

	CaptureSettings.bOverride_AmbientOcclusionQuality = true;
	CaptureSettings.bOverride_MotionBlurAmount = true;
	CaptureSettings.bOverride_SceneFringeIntensity = true;
	CaptureSettings.bOverride_ScreenSpaceReflectionQuality = true;

	CaptureSettings.AmbientOcclusionQuality = 0.0f; //0=lowest quality..100=maximum quality
	CaptureSettings.MotionBlurAmount = 0.0f; //0 = disabled
	CaptureSettings.SceneFringeIntensity = 0.0f; //0 = disabled
	CaptureSettings.ScreenSpaceReflectionQuality = 0.0f; //0 = disabled

	SceneCapture->PostProcessSettings = CaptureSettings;

	GeneratePortalTexture();
}

void AABSPortal::GeneratePortalTexture()
{
	int32 CurrentSizeX = 1920;
	int32 CurrentSizeY = 1080;
	
	// Create the RenderTarget if it does not exist
	if( PortalTexture == nullptr )
	{
		// Create new RTT
		PortalTexture = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("PortalRenderTarget"));
		check( PortalTexture );
        
		PortalTexture->RenderTargetFormat = RTF_RGBA16f;
		PortalTexture->Filter = TF_Bilinear;
		PortalTexture->SizeX = CurrentSizeX;
		PortalTexture->SizeY = CurrentSizeY;
		PortalTexture->ClearColor = FLinearColor::Black;
		PortalTexture->TargetGamma = 2.2f;
		PortalTexture->bNeedsTwoCopies = false;
		PortalTexture->AddressX = TA_Clamp;
		PortalTexture->AddressY = TA_Clamp;

		// Not needed since the texture is displayed on screen directly
		// in some engine versions this can even lead to crashes (notably 4.24/4.25)
		PortalTexture->bAutoGenerateMips    = false;

		// This force the engine to create the render target 
		// with the parameters we defined just above
		PortalTexture->UpdateResource();
	}
}
 void AABSPortal::BeginPlay()
{
	Super::BeginPlay();
	PortalMesh->OnComponentBeginOverlap.AddDynamic(this,&AABSPortal::MeshOverlapBegin);
	PortalMesh->OnComponentEndOverlap.AddDynamic(this,&AABSPortal::MeshOverlapEnd);	
	FrontBoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AABSPortal::FrontBoxOverlapBegin);
	FrontBoxComponent->OnComponentEndOverlap.AddDynamic(this,&AABSPortal::FrontBoxOverlapEnd);
}

 void AABSPortal::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	if(bIsNearPortal)
	{
		CheckForTeleport();
	}
 }

void AABSPortal::FrontBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsNearPortal = true;
	TriggeringActor = OtherActor;
}

void AABSPortal::FrontBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsNearPortal = false;
	TriggeringActor = nullptr;
}

void AABSPortal::MeshOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StoredCollisionChannel = OtherComp->GetCollisionObjectType();
	OtherComp->SetCollisionObjectType(ECC_GameTraceChannel1);
}

void AABSPortal::MeshOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OtherComp->SetCollisionObjectType(StoredCollisionChannel);
}

void AABSPortal::CheckForTeleport()
{
	FVector ActorLocation = TriggeringActor->GetActorLocation();
	
	if(IsPointCrossingPortal(ActorLocation))
	{
		if (TriggeringActor->IsA(AABSPlayerCharacter::StaticClass()))
		{
			AABSPlayerCharacter* ActorToTeleport = Cast<AABSPlayerCharacter>(TriggeringActor);
			ActorToTeleport->GetPlayerController()->PortalManager->RequestTeleportByPortal(this, TriggeringActor);
		}
	}
}

bool AABSPortal::IsPointCrossingPortal(FVector Point)
{
	bIsCrossing = false;

	bIsBehind = PortalHelper->IsPointInsideBox(Point, BackBoxComponent);

	if(bWasInFront && bIsBehind)
	{
		bIsCrossing  = true;
	}

	bWasInFront = PortalHelper->IsPointInsideBox(Point, FrontBoxComponent);
	
	if(bIsCrossing)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Portal Crossed"));
	}
	return bIsCrossing;
}

void AABSPortal::TeleportActor(AActor* ActorToTeleport)
{
	if(ActorToTeleport == nullptr || Target == nullptr)
	{
		return;
	}

	//-------------------------------
	//Retrieve and save Player Velocity
	//(from the Movement Component)
	//-------------------------------
	FVector SavedVelocity = FVector::ZeroVector;
	AABSPlayerCharacter* PC = nullptr;

	if( ActorToTeleport->IsA(AABSPlayerCharacter::StaticClass()))
	{
		PC = Cast<AABSPlayerCharacter>(ActorToTeleport);
		SavedVelocity = PC->GetVelocity();
	}
	
	//-------------------------------
	//Compute and apply new location
	//-------------------------------
	FHitResult HitResult;
	FVector NewLocation = PortalHelper->ConvertLocationToActorSpace(ActorToTeleport->GetActorLocation(), this, Target);

	//-------------------------------
	//Compute and apply new rotation
	//-------------------------------
	FRotator NewRotation = PortalHelper->ConvertRotationToActorSpace(ActorToTeleport->GetActorRotation(), this, Target);
	FRotator InvertRotation = FRotator(0.0f, 180.0f, 0.0f);

	ActorToTeleport->SetActorLocation(NewLocation, false, &HitResult, ETeleportType::TeleportPhysics );
	ActorToTeleport->SetActorRelativeRotation(NewRotation + InvertRotation);
	
	//-------------------------------
	//If we are teleporting a character we need to    
	//update its controller as well and reapply its velocity
	//-------------------------------
	if(ActorToTeleport->IsA(AABSPlayerCharacter::StaticClass()))
	{
		//Update Controller
		AABSPlayerController* APC = PC->GetPlayerController();
		
		if( APC != nullptr )
		{
			
			NewRotation = PortalHelper->ConvertRotationToActorSpace(APC->GetControlRotation(), this, Target);
			APC->SetControlRotation(NewRotation += InvertRotation);
		}

		//Reapply Velocity (Need to reorient direction into local space of Portal)
		{
			FVector Dots;
			Dots.X  = FVector::DotProduct( SavedVelocity, GetActorForwardVector() );
			Dots.Y  = FVector::DotProduct( SavedVelocity, GetActorRightVector() );
			Dots.Z  = FVector::DotProduct( SavedVelocity, GetActorUpVector() );

			FVector TargetVector = FVector(Target->GetActorForwardVector() + Target->GetActorRightVector() + Target->GetActorUpVector() );
			FVector NewVelocity = Dots * TargetVector;

			PC->PostNetReceiveVelocity(NewVelocity);
		}
	}

	//Cleanup Teleport
	LastPosition = NewLocation;
}


