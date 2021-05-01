// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TA_CharacterBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATA_CharacterBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class ATA_WeaponRangeBase* WeaponSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	bool bIsAttacking;

	FName SocketWeapon;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	class ATA_WeaponRangeBase* GetSelectedWeapon() { return WeaponSelected; }

	UFUNCTION(BlueprintCallable, Category="Weapon Equip")
	void EquipWeapon(TSubclassOf<ATA_WeaponRangeBase> WeaponClass);
	
	void UnEquipWeapon();
};
