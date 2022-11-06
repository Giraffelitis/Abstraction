// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

// Sets default values
ADamageComponent::ADamageComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamageComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

