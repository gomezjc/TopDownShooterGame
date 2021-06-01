// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TA_HUD.generated.h"

UCLASS()
class TINY_APOCALYPSE_API UTA_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	FText WeaponName;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	int32 WeaponBullets;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	int32 InventoryBullets;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	class ATA_Player* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	float MaxHealth = 0;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	float HealthPercentage;

	UPROPERTY(BlueprintReadOnly, Category="Setup")
	FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	FLinearColor EmptyHealthColor;
	
	UFUNCTION()
	void UpdateWeapon(class ATA_WeaponBase* WeaponSelected);

	UFUNCTION()
	void UpdateBullets(int32 CurrentBullets);

	UFUNCTION()
	void UnEquipWeapon(class ATA_WeaponBase* WeaponSelected);

	UFUNCTION()
	void OnHealthChange(float CurrentHealth);
public:
	UFUNCTION(BlueprintCallable, Category="Setup")
	void InitializeWidget();
};
