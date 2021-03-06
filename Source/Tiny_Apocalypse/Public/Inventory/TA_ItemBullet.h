// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/TA_ItemInventory.h"
#include "Utils/Enums/ETA_BulletType.h"
#include "TA_ItemBullet.generated.h"

UCLASS()
class TINY_APOCALYPSE_API UTA_ItemBullet : public UTA_ItemInventory
{
	GENERATED_BODY()

public:
	UTA_ItemBullet();

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	int32 ReloadMagazine(int32 MagazineCapacity);
	
	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	ETA_BulletType GetBulletType() const { return BulletType; }

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	void SetBulletType(ETA_BulletType BulletType);
	
	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	int32 GetQuantity() const { return Quantity; };

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	int32 GetMagazineWeapon();
	
	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	void SetQuantity(int32 Quantity);

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	void SetMagazineWeapon(int32 Value);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	ETA_BulletType BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	int32 Quantity = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	int32 MagazineWeapon = 0;
};
