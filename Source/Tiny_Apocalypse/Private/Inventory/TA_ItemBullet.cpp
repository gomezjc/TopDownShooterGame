// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/TA_ItemBullet.h"

UTA_ItemBullet::UTA_ItemBullet()
{
	ItemType = ETA_ItemType::ItemType_Bullet;
}

int32 UTA_ItemBullet::ReloadMagazine(int32 MagazineCapacity)
{
	Quantity = MagazineWeapon + Quantity;
	MagazineWeapon = FMath::Clamp(Quantity, 0, MagazineCapacity);
	Quantity = FMath::Clamp(Quantity - MagazineWeapon, 0, Quantity);
	return MagazineWeapon;
}

void UTA_ItemBullet::SetBulletType(ETA_BulletType BulletTypeParam)
{
	BulletType = BulletTypeParam;
}

int32 UTA_ItemBullet::GetMagazineWeapon()
{
	return MagazineWeapon;
}

void UTA_ItemBullet::SetQuantity(int32 QuantityParam)
{
	Quantity = QuantityParam;
}
