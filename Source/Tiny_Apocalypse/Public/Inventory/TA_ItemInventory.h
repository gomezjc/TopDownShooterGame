// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Utils/Enums/ETA_ItemType.h"
#include "TA_ItemInventory.generated.h"

UCLASS()
class TINY_APOCALYPSE_API UTA_ItemInventory : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	ETA_ItemType GetItemType() const { return ItemType; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	ETA_ItemType ItemType;
};
