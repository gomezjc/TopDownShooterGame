// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectables/TA_ItemCollectable.h"
#include "Utils/Enums/ETA_BulletType.h"
#include "TA_BulletCollectable.generated.h"

/**
 * 
 */
UCLASS()
class TINY_APOCALYPSE_API ATA_BulletCollectable : public ATA_ItemCollectable
{
	GENERATED_BODY()

public:
	ATA_BulletCollectable();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullets")
	ETA_BulletType BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Bullets")
	int32 QuantityToPick = 0;

	virtual void OnInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	UFUNCTION(BlueprintCallable, Category="Inventory|Bullets")
	ETA_BulletType GetBulletType() { return BulletType; }

	UFUNCTION(BlueprintCallable, Category="Inventory|Bullets")
	int32 GetQuantityToPick() { return QuantityToPick; };
};
