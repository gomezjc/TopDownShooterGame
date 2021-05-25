// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums/ETA_WeaponType.h"
#include "TA_WeaponBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATA_WeaponBase();

protected:

	UPROPERTY(EditAnywhere, Category="Weapon")
	FText WeaponName;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	ETA_WeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ATA_WeaponBase> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsPlayer(AActor* OtherActor);

public:

	virtual void StartWeaponAction();

	virtual void StopWeaponAction();

	virtual void OnWeaponEquipped();

	virtual void OnWeaponUnEquipped();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StartWeaponAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StopWeaponAction();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ETA_WeaponType GetWeaponType() { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<ATA_WeaponBase> GetWeaponClass() { return WeaponClass; }

	UFUNCTION(BlueprintCallable, Category="Weapon")
	FText GetWeaponName() { return WeaponName; }
};
