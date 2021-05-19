// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TA_CharacterBase.h"
#include "Components/TimelineComponent.h"
#include "Utils/Enums/ETA_BulletType.h"
#include "TA_Player.generated.h"

/**
 * 
 */
UCLASS()
class TINY_APOCALYPSE_API ATA_Player : public ATA_CharacterBase
{
	GENERATED_BODY()

public:
	ATA_Player();

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
	
protected:

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Roll();

	void Reload();

	bool WeaponNeedReload();
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
