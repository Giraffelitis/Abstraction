// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractAction.h"
#include "ABSInteractionComponent.h"
#include "ABSGameplayInterface.h"
#include "ABSObjectiveComponent.h"
#include "DrawDebugHelpers.h"
#include "ABSWorldUserWidget.h"


static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);


UABSInteractAction::UABSInteractAction()
{
	PrimaryComponentTick.bCanEverTick = true;
	bInteractSuccess = false;

	// We are using Camera info in Tick so we want the most up to date camera position for tracing
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;

	//Set the distance and radius for the trace to locate interactable objects and set the collision channel set for interaction
	TraceRadius = 30.0f;
	TraceDistance = 500.0f;
	CollisionChannel = ECC_WorldDynamic;
}

void UABSInteractAction::BeginPlay()
{
	Super::BeginPlay();
}

void UABSInteractAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

void UABSInteractAction::FindBestInteractable()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	// Check for collisions based on CollisionChannel
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel); 

	// Gets Actor to start trace from and their EyeLocation and Rotation
	AActor* MyOwner = GetOwner(); 
	FVector EyeLocation;
	FRotator EyeRotation;

	// Sets Start point of trace
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);  

	//Sets end point of trace for interaction
	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance); 

	// Collects all Actors hit with Sweep
	TArray<FHitResult> Hits; 

	// Sets shape and size for the end of the trace is used to make easier interaction and not needing pinpoint accuracy for smaller objects
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius); 

	// Fires sweep and returns all objects collided with based on params above
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	// Sets debug info colors
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Clears ref before trying to fill
	FocusedActor = nullptr;

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UABSGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		
		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<UABSWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 0.0f);
	}
}


void UABSInteractAction::PrimaryInteract()
{
	Interact(FocusedActor);
}


void UABSInteractAction::Interact(AActor* InFocus)
{
	if (InFocus == nullptr)
	{
		return;
	}

	AActor* MyOwner = GetOwner();
	check(MyOwner)
	
	UABSInteractionComponent* InteractComp = InFocus->FindComponentByClass<UABSInteractionComponent>();
	
	if(InteractComp)
	{
		bInteractSuccess = InteractComp->InteractedWith(MyOwner);
	}
	UpdateObjective(InFocus);
}

void UABSInteractAction::UpdateObjective(AActor* InFocus)
{
	if(bInteractSuccess)
	{
		// Build array to collect and loop through if there are multiple objective components on a single actor 
		TInlineComponentArray<UABSObjectiveComponent*> ObjectiveCompArray;
		InFocus->GetComponents(ObjectiveCompArray);
		if(!ObjectiveCompArray.IsEmpty())
		{
			for (UABSObjectiveComponent* ObjectiveComp : ObjectiveCompArray)
			{
				if(ObjectiveComp)
				{	
					ObjectiveComp->OnObjectiveInteractWith();
				}
			}
			bInteractSuccess = false;
		}
	}
}