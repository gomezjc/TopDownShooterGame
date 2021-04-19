// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_WeaponRocket.h"

ATA_WeaponRocket::ATA_WeaponRocket()
{
	WeaponType = ETA_WeaponType::WeaponType_Rocket;
}

void ATA_WeaponRocket::PickUpWeapon()
{
	if (bCanPickUp)
	{

	}
}

void ATA_WeaponRocket::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATA_WeaponRocket::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}