// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums/ETA_WeaponType.h"
#include "TA_WeaponRangeBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponRangeBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATA_WeaponRangeBase();

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	ETA_WeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UBoxComponent* WeaponCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ATA_WeaponRangeBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Range")
	class UArrowComponent* MuzzleComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsPlayer(AActor* OtherActor);

public:

	UFUNCTION(BlueprintCallable, Category="Weapon")
	ETA_WeaponType GetWeaponType() { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<ATA_WeaponRangeBase> GetWeaponClass() { return WeaponClass; }

};