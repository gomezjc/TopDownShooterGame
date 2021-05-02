// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TA_WeaponBase.h"
#include "TA_WeaponRangeBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponRangeBase : public ATA_WeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATA_WeaponRangeBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Range")
	class UArrowComponent* MuzzleComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Range")
	class TSubclassOf<class ATA_BulletBase> BulletClass;

protected:
	virtual void BeginPlay() override;

	virtual void StartWeaponAction() override;
};