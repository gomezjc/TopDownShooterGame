// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/TA_ItemBullet.h"

UTA_ItemBullet::UTA_ItemBullet()
{
	ItemType = ETA_ItemType::ItemType_Bullet;
}

int32 UTA_ItemBullet::UpdateQuantity(int32 Value)
{
	Quantity = FMath::Clamp((Value + Quantity), 0, MaxQuantity);
	return Quantity;
}
