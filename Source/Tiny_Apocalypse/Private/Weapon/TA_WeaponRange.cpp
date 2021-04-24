// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_WeaponRange.h"

ATA_WeaponRange::ATA_WeaponRange()
{
	WeaponType = ETA_WeaponType::WeaponType_Pistol;
}

void ATA_WeaponRange::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATA_WeaponRange::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
