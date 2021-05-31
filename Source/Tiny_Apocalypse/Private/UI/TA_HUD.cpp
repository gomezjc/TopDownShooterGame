// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TA_HUD.h"
#include "Character/TA_HealthComponent.h"
#include "Inventory/TA_ItemBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TA_Player.h"
#include "Weapon/TA_WeaponBase.h"
#include "Weapon/TA_WeaponRangeBase.h"

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
			Player->OnWeaponShootDelegate.AddDynamic(this, &UTA_HUD::UpdateBullets);
			UTA_HealthComponent* HealthComponent = Player->GetHealthComponent();

			if (IsValid(HealthComponent))
			{
				MaxHealth = HealthComponent->MaxHealth;
				HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &UTA_HUD::OnHealthChange);
			}
		}
	}
}


void UTA_HUD::UpdateWeapon(ATA_WeaponBase* WeaponSelected)
{
	if (IsValid(WeaponSelected))
	{
		WeaponName = WeaponSelected->GetWeaponName();
		ATA_WeaponRangeBase* WeaponRangeSelected = Cast<ATA_WeaponRangeBase>(WeaponSelected);
		if (IsValid(WeaponRangeSelected))
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD_WEAPON: ADD RANGE"));
			WeaponBullets = WeaponRangeSelected->GetCurrentBullets();
			UTA_ItemBullet* BulletInventory = WeaponRangeSelected->GetBulletsFromInventory();
			if (IsValid(BulletInventory))
			{
				InventoryBullets = BulletInventory->GetQuantity();
			}
		}
	}
}

void UTA_HUD::UpdateBullets(int32 CurrentBullets)
{
	WeaponBullets = CurrentBullets;
}

void UTA_HUD::UnEquipWeapon(ATA_WeaponBase* WeaponSelected)
{
}

void UTA_HUD::OnHealthChange(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthChange %f / %f"), Value, MaxHealth);
}