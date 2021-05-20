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
	int32 UpdateQuantity(int32 Value);

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	int32 GetQuantity() const { return Quantity; };

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	int32 GetMaxQuantity() const { return MaxQuantity; };

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullet")
	ETA_BulletType GetBulletType() const { return BulletType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	ETA_BulletType BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullet")
	int32 MaxQuantity = 0;
};
