// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/TA_ItemCollectable.h"

// Sets default values
ATA_ItemCollectable::ATA_ItemCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATA_ItemCollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATA_ItemCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

