// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "ABSEnhancedInputComponent.h"
#include "ABSInteractionComponent.h"
#include "ABSGameplayTags.h"
#include "ABSInteractAction.h"
#include "ABSActionComponent.h"
#include "ABSPlayerController.h"
#include "ABSPortalManager.h"
#include "ABSPortalProjectile.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AABSPlayerCharacter::AABSPlayerCharacter()
: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UABSInteractionComponent>(TEXT("Interaction Component"));
	InteractAction = CreateDefaultSubobject<UABSInteractAction>("InteractAction");
	ActionComp = CreateDefaultSubobject<UABSActionComponent>("ActionComp");
	PortalManagerComp = CreateDefaultSubobject<UABSPortalManager>(TEXT("PortalManagerComp"));

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	PlayerCameraComponent->SetupAttachment(SpringArmComp);
	PlayerCameraComponent->bUsePawnControlRotation = true;
	
}

void AABSPlayerCharacter::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if( UGameplayStatics::GetPlayerController(GetWorld(), 0) != nullptr )
	{
		PortalManagerComp->Update(DeltaTime);
	}
}

AABSPlayerController* AABSPlayerCharacter::GetPlayerController()
{
	if( UGameplayStatics::GetPlayerController(GetWorld(), 0) != nullptr )
	{
		AABSPlayerController* PC = Cast<AABSPlayerController>( UGameplayStatics::GetPlayerController(GetWorld(), 0) );
		return PC;
	}
	return nullptr;
}
// Called when the game starts or when spawned
void AABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PortalManagerComp->SetControllerOwner(this->GetPlayerController());
	PortalManagerComp->Init();
}


// Called every frame
void AABSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	FRotator UpdatedRotation = CurrentRotation;
	if(CurrentRotation.Roll > 0 + KINDA_SMALL_NUMBER)
	{
		UpdatedRotation.Roll *= 0.9f;
	}
	else if(CurrentRotation.Roll < 0 - KINDA_SMALL_NUMBER)
	{
		UpdatedRotation.Roll *= 0.9f;
	}

	if(CurrentRotation.Pitch > 0 + KINDA_SMALL_NUMBER)
	{
		UpdatedRotation.Pitch *= 0.9f;
	}
	else if(CurrentRotation.Pitch < 0 - KINDA_SMALL_NUMBER)
	{
		UpdatedRotation.Pitch *= 0.9f;
	}

	this->SetActorRotation(UpdatedRotation);		
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
	//ActionComp->StartActionByName(this, "PrimaryAttack");

	FVector LHandLocation = GetMesh()->GetSocketLocation("hand_lSocket");

	FTransform SpawnTM = FTransform(GetControlRotation(), LHandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	PortalManagerComp->PortalProjectile = GetWorld()->SpawnActor<AABSPortalProjectile>(PortalProjectileClass, SpawnTM, SpawnParams);
	PortalManagerComp->NewLeftPortalProjectile.Broadcast();
}

void AABSPlayerCharacter::SecondaryAttack(const FInputActionValue& InputActionValue)
{
	//ActionComp->StartActionByName(this, "SecondaryAttack");
	
	FVector RHandLocation = GetMesh()->GetSocketLocation("hand_rSocket");
	
	FTransform SpawnTM = FTransform(GetControlRotation(), RHandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PortalManagerComp->PortalProjectile = GetWorld()->SpawnActor<AABSPortalProjectile>(PortalProjectileClass, SpawnTM, SpawnParams);
	PortalManagerComp->NewRightPortalProjectile.Broadcast();
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