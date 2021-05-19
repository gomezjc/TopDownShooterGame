// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ETA_BulletType.generated.h"

UENUM(Blueprintable)
enum class ETA_BulletType : uint8
{
	BulletType_Pistol  UMETA(DisplayName = "Pistol"),
	BulletType_Weapon  UMETA(DisplayName = "Weapon"),
	BulletType_Rocket  UMETA(DisplayName = "Rocket")
};