// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_Weapon_Machinegun.h"

ATA_Weapon_Machinegun::ATA_Weapon_Machinegun()
{
	WeaponType = ETA_WeaponType::WeaponType_Weapon;
}

void ATA_Weapon_Machinegun::PickUpWeapon()
{
	if (bCanPickUp)
	{

	}
}

void ATA_Weapon_Machinegun::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATA_Weapon_Machinegun::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}