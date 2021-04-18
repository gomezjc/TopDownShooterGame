// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/TA_WeaponBase.h"
#include "TA_WeaponMelee.generated.h"

/**
 * 
 */
UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponMelee : public ATA_WeaponBase
{
	GENERATED_BODY()

public:
	ATA_WeaponMelee();
	
protected:

	virtual void PickUpWeapon() override;

	virtual void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};