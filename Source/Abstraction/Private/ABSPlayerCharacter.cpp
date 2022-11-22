// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "ABSEnhancedInputComponent.h"
#include "ABSInteractionComponent.h"
#include "ABSGameplayTags.h"
#include "ABSInteractAction.h"
#include "ABSActionComponent.h"

// Sets default values
AABSPlayerCharacter::AABSPlayerCharacter()
: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	InteractAction = CreateDefaultSubobject<UABSInteractAction>("InteractAction");
	ActionComp = CreateDefaultSubobject<UABSActionComponent>("ActionComp");

	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	PlayerCameraComponent->SetupAttachment(GetCapsuleComponent());
	PlayerCameraComponent->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void AABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AABSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UABSEnhancedInputComponent* ABSEnhancedInputComponent = Cast<UABSEnhancedInputComponent>(PlayerInputComponent);
	
	check(ABSEnhancedInputComponent);

	const FABSGameplayTags& GameplayTags = FABSGameplayTags::Get();

	//Bind Input actions by tag
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Input_Move);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Input_Look);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Input_Look);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Input_Jump);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact_Primary, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::PrimaryInteract);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact_Secondary, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::SecondaryInteract);
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Attack_Primary, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::PrimaryAttack);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Attack_Secondary, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::SecondaryAttack);
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Sprint, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::SprintStart);	
	ABSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Parry, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Parry);

}

void AABSPlayerCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}


void AABSPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
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

void AABSPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
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

void AABSPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AABSPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AABSPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AABSPlayerCharacter::SprintStart(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AABSPlayerCharacter::SprintStop(const FInputActionValue& InputActionValue)
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AABSPlayerCharacter::PrimaryAttack(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void AABSPlayerCharacter::SecondaryAttack(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void AABSPlayerCharacter::Parry(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this, "Parry");
}

void AABSPlayerCharacter::PrimaryInteract(const FInputActionValue& InputActionValue)
{
	if (InteractAction)
	{
		InteractAction->PrimaryInteract();
	}
}

void AABSPlayerCharacter::SecondaryInteract(const FInputActionValue& InputActionValue)
{
	if (InteractAction)
	{
		InteractAction->PrimaryInteract();
	}
}

void  AABSPlayerCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath(true);
}

void AABSPlayerCharacter::OnDeath(bool IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}
