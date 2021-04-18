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

protected:

	virtual void PickUpWeapon() override;
	
public:
	ATA_WeaponMelee();
};
