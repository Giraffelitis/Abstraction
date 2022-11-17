// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "ABSEnhancedInputComponent.h"
#include "ABSGameplayTags.h"
#include "ABSInteractionComponent.h"
#include "ABSActionComponent.h"

// Sets default values
AABSPlayerCharacter::AABSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>("InteractionComp");
	ActionComp = CreateDefaultSubobject<UABSActionComponent>("ActionComp");
}

// Called when the game starts or when spawned
void AABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AABSPlayerCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}


void AABSPlayerCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}


void AABSPlayerCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AABSPlayerCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


void AABSPlayerCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void AABSPlayerCharacter::Dash()
{
	ActionComp->StartActionByName(this, "Dash");
}

void AABSPlayerCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
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

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(ABSEnhancedInputComponent);

	const FABSGameplayTags& GameplayTags = FABSGameplayTags::Get();

	//Bind Input actions by tag
	ABSEnhancedInputComponent->BindActionByTag(ABSInputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &AABSPlayerCharacter::Input_Move);
	ABSEnhancedInputComponent->BindAxis("MoveRight", this, &AABSPlayerCharacter::MoveRight);
	ABSEnhancedInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	ABSEnhancedInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	ABSEnhancedInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AABSPlayerCharacter::PrimaryAttack);
	ABSEnhancedInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AABSPlayerCharacter::PrimaryInteract);
	ABSEnhancedInputComponent->BindAction("Sprint", IE_Pressed, this, &AABSPlayerCharacter::SprintStart);
	ABSEnhancedInputComponent->BindAction("Sprint", IE_Released, this, &AABSPlayerCharacter::SprintStop);
	ABSEnhancedInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Fire;
	FGameplayTag InputTag_Interact;
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
