// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSAttributeComponent.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);


UABSAttributeComponent::UABSAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}


bool UABSAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}


bool UABSAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UABSAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}


float UABSAttributeComponent::GetHealth() const
{
	return Health;
}

float UABSAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}


bool UABSAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if ( Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;

	return ActualDelta != 0;
}


UABSAttributeComponent* UABSAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UABSAttributeComponent>();
	}

	return nullptr;
}


bool UABSAttributeComponent::IsActorAlive(AActor* Actor)
{
	UABSAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}
