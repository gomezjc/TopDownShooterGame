// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TA_CharacterBase.h"
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
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void StartAction();

	void StopAction();

public:
};
