// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "ObjectiveComponent.h"
#include "InteractionComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "AbstractionPlayerCharacter.h"

constexpr float FLT_METERS(float meters) { return meters * 50.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugButton(
	TEXT("Abstraction.ButtonInteractionComponent.Debug"),
	false,
	TEXT("Toggle ButtonInteractionComponent debug display"),
	ECVF_Default);

// Sets default values for this component's properties
UButtonInteractionComponent::UButtonInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ButtonState = EButtonState::BS_In;

	CVarToggleDebugButton.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UButtonInteractionComponent::OnDebugToggled));
}

void UButtonInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ButtonState == EButtonState::BS_In)
	{
		CurrentPressedTime += DeltaTime;
		if (CurrentPressedTime >= TimeToRelease)
		{
			ButtonState = EButtonState::BS_Out;
		}
	}

	DebugDraw();
}

void UButtonInteractionComponent::PressButton()
{
	if (ButtonState == EButtonState::BS_In)
	{
		return;
	}

	if (AudioComponent)
	{
		AudioComponent->Play();
	}

	ButtonState = EButtonState::BS_In;
	CurrentPressedTime = 0.0f;
}

void UButtonInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//ensure TimeToRotate is greater than EPSILON
	CurrentPressedTime = 0.0f;

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	//check(AudioComponent);
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UButtonInteractionComponent::BeginPlay() Missing Audio Component"));
	}

	TextRenderComponent = GetOwner()->FindComponentByClass<UTextRenderComponent>();
}

void UButtonInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UButtonInteractionComponent::OnOverlapBegin"));
	//we already have somebody interacting, currently we don't support multiple interactions
	if (InteractingActor || !bActive)
	{
		return;
	}

	//for now we will get that component and set visible
	if (OtherActor->ActorHasTag("Player"))
	{
		InteractingActor = OtherActor;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetText(InteractionPrompt);
			TextRenderComponent->SetVisibility(true);
		}
	}
}

void UButtonInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UButtonInteractionComponent::OnOverlapEnd"));
	if (OtherActor == InteractingActor)
	{
		InteractingActor = nullptr;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetVisibility(false);
		}
	}
}

void UButtonInteractionComponent::InteractionRequested()
{
	//ideally we would make sure this is allowed
	if (InteractingActor)
	{
		bActive = false;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetText(InteractionPrompt);
			TextRenderComponent->SetVisibility(false);
		}

		AAbstractionPlayerCharacter* APC = Cast<AAbstractionPlayerCharacter>(InteractingActor);
		if (APC)
		{
			APC->ButtonPressInteractionStarted(GetOwner());
		}
	}
}



void UButtonInteractionComponent::OnButtonPressed()
{
	ButtonState = EButtonState::BS_In;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}

	//hide prompt
	//disable interaction

	InteractionSuccess.Broadcast();
}

void UButtonInteractionComponent::OnDebugToggled(IConsoleVariable* Var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UButtonInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugButton->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Button State: ") + UEnum::GetDisplayValueAsText(ButtonState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}