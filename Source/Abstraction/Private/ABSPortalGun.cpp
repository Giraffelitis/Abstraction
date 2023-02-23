// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSPortalGun.h"
#include "ABSPlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AABSPortalGun::AABSPortalGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AABSPortalGun::OnOverlapBegin);
	SphereComponent->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AABSPortalGun::BeginPlay()
{
	Super::BeginPlay();	
}

void AABSPortalGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AABSPlayerCharacter::StaticClass()))
		{
			this->AttachToComponent(OtherActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
		}
}

// Called every frame
void AABSPortalGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
FVector RHandLocation = GetMesh()->GetSocketLocation("hand_rSocket");
	
FTransform SpawnTM = FTransform(GetControlRotation(), RHandLocation);

FActorSpawnParameters SpawnParams;
SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

PortalManagerComp->PortalProjectile = GetWorld()->SpawnActor<AABSPortalProjectile>(PortalProjectileClass, SpawnTM, SpawnParams);
PortalManagerComp->NewRightPortalProjectile.Broadcast();
*/