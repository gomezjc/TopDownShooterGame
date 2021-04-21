// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/TA_WeaponBase.h"
#include "TA_Weapon_Machinegun.generated.h"

/**
 * 
 */
UCLASS()
class TINY_APOCALYPSE_API ATA_Weapon_Machinegun : public ATA_WeaponBase
{
	GENERATED_BODY()

public:
	ATA_Weapon_Machinegun();

protected:

	virtual void PickUpWeapon() override;

	virtual void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
