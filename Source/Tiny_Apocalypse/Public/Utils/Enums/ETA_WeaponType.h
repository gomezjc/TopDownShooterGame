// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ETA_WeaponType.generated.h"

UENUM(Blueprintable)
enum class ETA_WeaponType : uint8
{
	WeaponType_None    UMETA(DisplayName = "None"),
	WeaponType_Melee   UMETA(DisplayName = "Melee"),
	WeaponType_Pistol  UMETA(DisplayName = "Pistol"),
	WeaponType_Weapon  UMETA(DisplayName = "Weapon"),
	WeaponType_Rocket  UMETA(DisplayName = "Rocket")
};