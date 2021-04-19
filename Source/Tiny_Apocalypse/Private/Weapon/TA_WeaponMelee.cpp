// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_WeaponMelee.h"
#include "Player/TA_Player.h"


ATA_WeaponMelee::ATA_WeaponMelee()
{
	WeaponType = ETA_WeaponType::WeaponType_Melee;
}

void ATA_WeaponMelee::PickUpWeapon()
{
	if(bCanPickUp)
	{
		
	}
}

void ATA_WeaponMelee::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATA_WeaponMelee::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
