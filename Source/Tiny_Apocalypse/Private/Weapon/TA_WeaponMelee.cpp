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
	if (IsPlayer(OtherActor))
	{
		ATA_Player* Player = Cast<ATA_Player>(OtherActor);
		bCanPickUp = true;
		Player->AttachWeapon(this);
		UE_LOG(LogTemp, Warning, TEXT("Entro Player"))
	}
}

void ATA_WeaponMelee::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsPlayer(OtherActor))
	{
		bCanPickUp = false;
		UE_LOG(LogTemp, Warning, TEXT("Salio Player"))
	}
}
