// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TA_WeaponBase.h"
#include "TA_WeaponMeleeBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_WeaponMeleeBase : public ATA_WeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATA_WeaponMeleeBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UBoxComponent* WeaponCollider;

	UFUNCTION()
	virtual void OnPlayerBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
