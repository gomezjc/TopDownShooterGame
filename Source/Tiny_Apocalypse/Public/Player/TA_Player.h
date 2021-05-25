// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TA_CharacterBase.h"
#include "Components/TimelineComponent.h"
#include "Utils/Enums/ETA_BulletType.h"
#include "TA_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChangeSignature, ATA_WeaponBase*, CurrentWeapon);

UCLASS()
class TINY_APOCALYPSE_API ATA_Player : public ATA_CharacterBase
{
	GENERATED_BODY()

public:
	ATA_Player();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Roll();
	void Reload();
	bool WeaponNeedReload();
	
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fight|Speed")
	float DefaultWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fight|Speed")
	float FightingWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Animation")
	bool bAnimateRangeWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation|Montages")
	class UAnimMontage* RollMontage;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* fCurve;

	class UAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Reload")
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Roll")
	bool bIsRolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Roll")
	float RollSpeed;

	FTimerHandle TimeHandle_Reload;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class UTA_ItemInventory*> InventoryData; 
	
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Animation")
	bool IsReloading() { return bIsReloading; }

	UFUNCTION(BlueprintCallable, Category="Weapon|Animation")
	void SetAnimateRangeWeapon(bool Value);

	void OnReloadComplete();
	
	void OnWeaponAction();

	void StartAction();

	void StopAction();

	void DisablePlayerMovement();

	void RecoverPlayerMovement();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	class ATA_WeaponBase* GetSelectedWeapon() { return WeaponSelected; }

	UFUNCTION(BlueprintCallable, Category="Weapon Equip")
	void EquipWeapon(TSubclassOf<ATA_WeaponBase> WeaponClass);
	
	void UnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItemToInventory(class UTA_ItemInventory* ItemInventory);

    UFUNCTION(BlueprintCallable, Category="Inventory")
	class UTA_ItemBullet* GetBulletByType(ETA_BulletType BulletType);

	UPROPERTY(BlueprintAssignable)
	FOnWeaponChangeSignature OnWeaponChangeDelegate;
	
private:
	class UTimelineComponent* RollTimeline;

	FOnTimelineFloat InterpolationRoll{};

	FOnTimelineEvent RollTimelineFinish{};

	FVector CurrentRollPosition;

	FVector DestinationRollPosition;

	UFUNCTION()
	void TimelineRollFloatReturn(float value);

	UFUNCTION()
	void OnTimelineRollFinished();
};
