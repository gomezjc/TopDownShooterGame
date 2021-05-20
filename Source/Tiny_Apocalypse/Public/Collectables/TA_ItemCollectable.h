// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TA_ItemCollectable.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_ItemCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATA_ItemCollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
