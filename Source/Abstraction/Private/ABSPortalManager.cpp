// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPortalManager.h"
#include "ABSPlayerCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ABSPlayerController.h"
#include "ABSPortal.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
UABSPortalManager::UABSPortalManager()
{
	UpdateDelay = 1.1f;

	PreviousScreenSizeX = 0;
	PreviousScreenSizeY = 0;
}

void UABSPortalManager::BeginPlay()
{
	Super::BeginPlay();

	AABSPlayerCharacter* PC = Cast<AABSPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	NewLeftPortalLocation.AddDynamic(this, &UABSPortalManager::SpawnLeftPortal);
	NewRightPortalLocation.AddDynamic(this, &UABSPortalManager::SpawnRightPortal);
}
void UABSPortalManager::Init()
{	
	//------------------------------------------------
	//Create RTT Buffer
	//------------------------------------------------
	UpdatePortalTexture();
}

void UABSPortalManager::UpdatePortalTexture()
{
	int32 CurrentSizeX = 1920;
	int32 CurrentSizeY = 1080;

	if( ControllerOwner != nullptr )
	{
		ControllerOwner->GetViewportSize(CurrentSizeX, CurrentSizeY);
	}

	// Use a smaller size than the current 
	// screen to reduce the performance impact
	CurrentSizeX = FMath::Clamp( int(CurrentSizeX / 1.7), 128, 1920); //1920 / 1.5 = 1280
	CurrentSizeY = FMath::Clamp( int(CurrentSizeY / 1.7), 128, 1080);

	if( CurrentSizeX == PreviousScreenSizeX
	&&  CurrentSizeY == PreviousScreenSizeY )
	{
		return;
	}

	PreviousScreenSizeX = CurrentSizeX;
	PreviousScreenSizeY = CurrentSizeY;

	if(IsValid(LeftPortal))
	{
		LeftPortal->PortalTexture->ResizeTarget(CurrentSizeX, CurrentSizeY);
	}
	if(IsValid(RightPortal))
	{
		RightPortal->PortalTexture->ResizeTarget(CurrentSizeX, CurrentSizeY);
	}
}

void UABSPortalManager::SetControllerOwner(AABSPlayerController* NewOwner )
{
	ControllerOwner = NewOwner;	
}

void UABSPortalManager::SpawnLeftPortal(FTransform SpawnTM)
{
	if(LeftPortal)
	{
		LeftPortal->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	LeftPortal = GetWorld()->SpawnActor<AABSPortal>(PortalToSpawn, SpawnTM, SpawnParams);
	if(RightPortal)
	{
		LeftPortal->Target = RightPortal;
		RightPortal->Target = LeftPortal;
	}
}
void UABSPortalManager::SpawnRightPortal(FTransform SpawnTM)
{
	if(RightPortal)
	{
		RightPortal->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	RightPortal = GetWorld()->SpawnActor<AABSPortal>(PortalToSpawn, SpawnTM, SpawnParams);
	if(LeftPortal)
	{
		RightPortal->Target = LeftPortal;
		LeftPortal->Target = RightPortal;
	}
}

void UABSPortalManager::Update( float DeltaTime )
{
	//-----------------------------------
	// Generate Portal texture ?
	//-----------------------------------
	UpdateDelay += DeltaTime;

	if( UpdateDelay > 1.0f )
	{
		UpdateDelay = 0.0f;
		UpdatePortalTexture();
	}

	//-----------------------------------
	// Find portals in the level and update them
	//-----------------------------------
	AABSPortal* Portal = UpdatePortalsInWorld();

	if( Portal != nullptr )
	{
		UpdateCapture(Portal);

		if(Portal->Target != nullptr)
		{
			UpdateCapture(Portal->Target);
		}
	}
}

AABSPortal* UABSPortalManager::UpdatePortalsInWorld()
{
	//-----------------------------------
	// Update Portal actors in the world (and active one if nearby)
	//-----------------------------------
	ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	AABSPortal* ActivePortal = nullptr;
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float Distance = 4096.0f;
	TArray<AActor*> FoundPortal;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABSPortal::StaticClass(), FoundPortal);
	
	TArray<AABSPortal*>PortalArray;
	for (AActor* CurrentActor : FoundPortal)
	{
		if (AABSPortal* CurrentPortal = Cast<AABSPortal>(CurrentActor))
	   {
			PortalArray.AddUnique(CurrentPortal);
	   }
	} 
	
	for(TActorIterator<AABSPortal>ActorItr(GetWorld()); ActorItr; ++ActorItr)		
	{
		
		AABSPortal* Portal = *ActorItr;
		FVector PortalLocation = Portal->GetActorLocation();

		// Reset Portal
		Portal->SetActive(false);

		// Find the closest Portal when the player is Standing in front of
		float NewDistance = FMath::Abs(FVector::Dist(PlayerLocation, PortalLocation));

		if(NewDistance < Distance)
		{
			Distance = NewDistance;
			ActivePortal = Portal;
		}
	}

	return ActivePortal;
}

void UABSPortalManager::UpdateCapture(AABSPortal* Portal)
{
    if( ControllerOwner == nullptr )
    {
        return;
    }

	AActor* Character = ControllerOwner->GetCharacter();	
    //-----------------------------------
    // Update SceneCapture (discard if there is no active portal)
    //-----------------------------------
    if(Portal != nullptr && Character != nullptr)
    {

        UCameraComponent* PlayerCamera = Character->FindComponentByClass<UCameraComponent>();
        AABSPortal* Target = Portal->GetTarget();

        //Place the SceneCapture to the Target
        if(Target != nullptr)
        {
        	//-------------------------------
            //Compute new Rotation in the space of thea
            //Target location
            //-------------------------------
            FTransform CameraTransform = PlayerCamera->GetComponentTransform();
            FTransform OriginPortalTransform = Portal->GetTransform();

        	FTransform SceneCaptureTransform = UKismetMathLibrary::MakeRelativeTransform(CameraTransform, OriginPortalTransform);

            //Update SceneCapture Position
            Target->SceneCapture->SetRelativeTransform(SceneCaptureTransform);

            //-------------------------------
            //Clip Plane : to ignore objects between the
            //SceneCapture and the Target of the portal
            //-------------------------------
            Target->SceneCapture->ClipPlaneNormal = Target->GetActorForwardVector();
            Target->SceneCapture->ClipPlaneBase = Target->GetActorLocation() - (Target->SceneCapture->ClipPlaneNormal); //Offset to avoid visible pixel border        	
        }

        // Switch on the valid Portal
        Portal->SetActive( true );

        // Assign the Render Target
    	Portal->SetRTT(Portal->PortalTexture);
        Portal->SceneCapture->TextureTarget = Portal->PortalTexture;
    	
        // Get the Projection Matrix
        Portal->SceneCapture->CustomProjectionMatrix = ControllerOwner->GetCameraProjectionMatrix();

        // Say Cheeeeese !
        Portal->SceneCapture->CaptureScene();
    }	
}

void UABSPortalManager::RequestTeleportByPortal(AABSPortal* Portal, AActor* TargetToTeleport)
{
	if(Portal != nullptr && TargetToTeleport != nullptr)
	{
		Portal->TeleportActor(TargetToTeleport);
	}
}