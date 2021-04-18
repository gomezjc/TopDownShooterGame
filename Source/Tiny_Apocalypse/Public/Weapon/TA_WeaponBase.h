// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TA_WeaponBase.generated.h"

UENUM(Blueprintable)
enum class ETA_WeaponType : uint8
{
	WeaponType_None    UMETA(DisplayName = "None"),
	WeaponType_Melee   UMETA(DisplayName = "Melee"),
	WeaponType_Pistol  UMETA(DisplayName = "Pistol"),
	WeaponType_Rocket  UMETA(DisplayName = "Rocket")
};
UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATA_WeaponBase();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ETA_WeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bCanPickUp;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UBoxComponent* WeaponCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ATA_WeaponBase> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsPlayer(AActor* OtherActor);

public:
	virtual void PickUpWeapon();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	ETA_WeaponType GetWeaponType() { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<ATA_WeaponBase> GetWeaponClass() { return WeaponClass; }

};
