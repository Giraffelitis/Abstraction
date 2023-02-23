// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSKey.h"

#include "ABSInteractionComponent.h"
#include "ABSPlayerCharacter.h"
#include "GameplayTagContainer.h"
#include "Components/SphereComponent.h"

// Sets default values
AABSKey::AABSKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	RootComponent = KeyMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AABSKey::OnOverlapBegin);
	SphereComponent->SetupAttachment(KeyMesh);
	
	DriftAmount = 0.2f;
	bIsFloatingUp = true;
	StartingLocation = GetActorLocation();	
}

// Called when the game starts or when spawned
void AABSKey::BeginPlay()
{
	Super::BeginPlay();
	
	MaxPosOffset = GetActorLocation() + FVector(0.0f, 0.0f, 10.0f);
	MaxNegOffset = GetActorLocation() - FVector(0.0f, 0.0f, 10.0f);	
}

// Called every frame
void AABSKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetActorLocation().Z >= MaxPosOffset.Z )
	{
		bIsFloatingUp = false;
	}
	else if(GetActorLocation().Z <= MaxNegOffset.Z )
	{
		bIsFloatingUp = true;
	}
	
	if(bIsFloatingUp)
	{
		this->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, DriftAmount));
	}
	else
	{
		this->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -DriftAmount));		
	}
	
	this->SetActorRotation(GetActorRotation() + FRotator(0.0f, 1.0f, 0.0f));
}

void AABSKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AABSPlayerCharacter::StaticClass()))
	{
		AABSPlayerCharacter* Player = Cast<AABSPlayerCharacter>(OtherActor);
		
		if(!ActiveGameplayTags.IsEmpty())
		{
			if(this->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Red")))
			{
				Player->InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Red"));
				this->Destroy();
			}
			 else if(this->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Green")))
			{
				Player->InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Green"));
				this->Destroy();
			}
			else if(this->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Blue")))
			{
				Player->InteractionComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("SecurityTag.Card.Blue"));
				this->Destroy();
			}
		}
	}
}
