// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPortalProjectile.h"
#include "ABSPlayerCharacter.h"
#include "ABSPortalManager.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AABSPortalProjectile::AABSPortalProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Portal");
	SphereComp->SetSphereRadius(64.0f);
	RootComponent = SphereComp;

	SphereComp->OnComponentHit.AddDynamic(this, &AABSPortalProjectile::OnHit);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("Effect Component");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComp->InitialSpeed = 2000.0f;
}


// Called when the game starts or when spawned
void AABSPortalProjectile::BeginPlay()
{
	Super::BeginPlay();
	PM = Cast<AABSPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->PortalManagerComp;
	PM->NewLeftPortalProjectile.AddDynamic(this, &AABSPortalProjectile::SetAsLeftPortal);
	PM->NewRightPortalProjectile.AddDynamic(this, &AABSPortalProjectile::SetAsRightPortal);
		
}
void AABSPortalProjectile::SetAsLeftPortal()
{
	bIsLeftPortalProjectile = true;
}

void AABSPortalProjectile::SetAsRightPortal()
{
	bIsLeftPortalProjectile = false;
}

void AABSPortalProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	UWorld* ActiveLevel = GetWorld();

	if(IsValid(ActiveLevel))
	{
		FVector HitLocation = Hit.ImpactPoint;
		FRotator HitRotation = UKismetMathLibrary::MakeRotFromX(Hit.Normal);

		FTransform SpawnTM = FTransform(HitRotation, HitLocation);

		if(bIsLeftPortalProjectile)
		{
			PM->NewLeftPortalLocation.Broadcast(SpawnTM);
		}
		else
		{
			PM->NewRightPortalLocation.Broadcast(SpawnTM);			
		}
	}
	this->Destroy();
}

// Called every frame
void AABSPortalProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

