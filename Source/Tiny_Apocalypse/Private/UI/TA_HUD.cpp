// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TA_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TA_Player.h"
#include "Weapon/TA_WeaponBase.h"

void UTA_HUD::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		ATA_Player* Player = Cast<ATA_Player>(PlayerPawn);
		if (IsValid(Player))
		{
			PlayerCharacter = Player;
			Player->OnWeaponChangeDelegate.AddDynamic(this, &UTA_HUD::UpdateWeapon);
		}
	}
}


void UTA_HUD::UpdateWeapon(ATA_WeaponBase* WeaponSelected)
{
	if (IsValid(WeaponSelected))
	{
		WeaponName = WeaponSelected->GetWeaponName();
	}
}