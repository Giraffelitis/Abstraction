// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSInteractAction.h"
#include "ABSInteractionComponent.h"
#include "ABSGameplayInterface.h"
#include "ABSItemChest.h"
#include "DrawDebugHelpers.h"
#include "ABSWorldUserWidget.h"


static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);


UABSInteractAction::UABSInteractAction()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Since we use Camera info in Tick we want the most up to date camera position for tracing
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;

	TraceRadius = 30.0f;
	TraceDistance = 500.0f;
	CollisionChannel = ECC_WorldDynamic;
}

void UABSInteractAction::Initialize(UABSInteractionComponent* NewActionComp)
{
	InteractionComp = NewActionComp;
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

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Clear ref before trying to fill
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

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Display Interact");
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
	
	UABSInteractionComponent* Comp = InFocus->FindComponentByClass<UABSInteractionComponent>();
	if(Comp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Component Found and Interaction was Broadcast");
		
		Comp->InteractedWith(MyOwner);
	}
}

UABSInteractionComponent* UABSInteractAction::GetOwningComponent() const
{
	return InteractionComp;
}