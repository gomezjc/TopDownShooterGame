// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TA_WeaponBase.h"
#include "Utils/Enums/ETA_BulletType.h"
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon|Range")
	float FireRate = 1;

	float FireCountdown = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fight|Animation")
	class UAnimMontage* ShootMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fight|Animation")
	class UAnimMontage* ReloadMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Range")
	int32 CurrentBullets = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon|Range")
	int32 MagazineCapacity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon|Range")
	ETA_BulletType BulletUsed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon|Range", meta=(ClampMin=0.0f, ClampMax=1.0f))
	float RecoilForcePercentage;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void StartWeaponAction() override;
	
	virtual void StopWeaponAction() override;

	virtual void OnWeaponEquipped() override;

	virtual void OnWeaponUnEquipped() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_FireRound();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Animation|Montage")
	void BP_ReloadComplete();

	UFUNCTION(BlueprintCallable, Category="Owner")
	class ATA_Player* GetPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Range")
	class UTA_ItemBullet* BulletWeapon;

	void ValidateMagazineInventory();
	
public:

	UFUNCTION(BlueprintCallable, Category="Weapon|Range")
	int32 GetCurrentBullets() { return CurrentBullets; }

	UFUNCTION(BlueprintCallable, Category="Weapon|Range")
	int32 GetMagazineCapacity() { return MagazineCapacity; }
	
	UFUNCTION(BlueprintCallable, Category="Animation|Montage")
	UAnimMontage* GetReloadMontage() { return ReloadMontage; }

	UFUNCTION(BlueprintCallable, Category = "Animation|Montage")
	void NotifyReloadComplete();

	UFUNCTION(BlueprintCallable, Category="Weapon|Range")
	class UTA_ItemBullet* GetBulletsFromInventory();
private:
	bool bCanShoot;
	void FireRound();
	void NotifyOwner();

	void SetMagazineWeapon();
};