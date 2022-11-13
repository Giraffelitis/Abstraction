// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "DamageHandlerComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "CustomEnhancedInputComponent.h"
#include "AbstractionGameplayTags.h"
#include "InteractionComponent.h"

// Sets default values
AAbstractionPlayerCharacter::AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UInteractionComponent>("InteractionComp");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

}

// Called when the game starts or when spawned
void AAbstractionPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//use possess/unpossess
	PC = GetWorld()->GetFirstPlayerController();
}

void AAbstractionPlayerCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
}

void AAbstractionPlayerCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AAbstractionPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void AAbstractionPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = InputActionValue.Get<FVector2D>();

		if (LookValue.X != 0.0f)
		{
			TurnAtRate(LookValue.X);
		}

		if (LookValue.Y != 0.0f)
		{
			LookUpAtRate(LookValue.Y);
		}
	}
}

void AAbstractionPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AAbstractionPlayerCharacter::Input_Fire(const FInputActionValue& InputActionValue)
{
	OnPrimaryAction();
}

void AAbstractionPlayerCharacter::Input_Interact(const FInputActionValue& InputActionValue)
{
	PrimaryInteract();
}

void AAbstractionPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AAbstractionPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void AAbstractionPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAbstractionPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Setup Custom Enhanced Input
	UCustomEnhancedInputComponent* CustomEnhancedInputComponent = Cast<UCustomEnhancedInputComponent>(PlayerInputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(CustomEnhancedInputComponent);

	const FAbstractionGameplayTags& GameplayTags = FAbstractionGameplayTags::Get();

	//Bind Input actions by tag
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Move);
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Look);
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Look);
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Fire, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Fire);
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Jump);
	CustomEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact, ETriggerEvent::Triggered, this, &AAbstractionPlayerCharacter::Input_Interact);
}

void  AAbstractionPlayerCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath(true);
}

float AAbstractionPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AAbstractionPlayerCharacter::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}

void AAbstractionPlayerCharacter::SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	if (DamageHandlerComponent)
	{
		DamageHandlerComponent->TakeFireDamage(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}	
}

void AAbstractionPlayerCharacter::OnDeath(bool IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void AAbstractionPlayerCharacter::HandleItemCollected()
{
	ItemsCollected++;
	// Play Effects here.
	PC->PlayerCameraManager->StartCameraShake(CamShake, 1.0f);
	PC->PlayDynamicForceFeedback(ForceFeedbackIntensity, ForceFeedbackDuration, true, false, true, false,
		EDynamicForceFeedbackAction::Start);
	
	ItemCollected();
}
