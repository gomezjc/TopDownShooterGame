// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ETA_ItemType.generated.h"

UENUM(Blueprintable)
enum class ETA_ItemType : uint8
{
	ItemType_Bullet  UMETA(DisplayName = "Bullet"),
	ItemType_Weapon  UMETA(DisplayName = "Weapon"),
	ItemType_Usable  UMETA(DisplayName = "Usable")
};
