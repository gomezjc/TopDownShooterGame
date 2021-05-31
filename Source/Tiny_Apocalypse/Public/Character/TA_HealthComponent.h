// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TA_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TINY_APOCALYPSE_API UTA_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTA_HealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float StartingHealth;

	UFUNCTION(BlueprintPure, Category="Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category="Health")
	bool IsDead();

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnHealthChange OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDied OnDiedDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	float CurrentHealth;

	UFUNCTION()
	void OnOwnerTakenDamage(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);
};
