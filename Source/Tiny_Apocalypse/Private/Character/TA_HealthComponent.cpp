// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TA_HealthComponent.h"

// Sets default values for this component's properties
UTA_HealthComponent::UTA_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingHealth = StartingHealth == 0 ? MaxHealth : StartingHealth;
	CurrentHealth = StartingHealth;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UTA_HealthComponent::OnOwnerTakenDamage);
	}
}

void UTA_HealthComponent::OnOwnerTakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp<float>(CurrentHealth - Damage, 0.0f, MaxHealth);
	OnHealthChangeDelegate.Broadcast(CurrentHealth);
	if(IsDead())
	{
		OnDiedDelegate.Broadcast();
	}
}

float UTA_HealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

bool UTA_HealthComponent::IsDead()
{
	return CurrentHealth <= 0.0f;
}
