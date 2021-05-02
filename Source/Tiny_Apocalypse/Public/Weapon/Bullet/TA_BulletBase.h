// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TA_BulletBase.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_BulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATA_BulletBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Bullet")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Bullet")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Bullet")
	class USphereComponent* HitSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
