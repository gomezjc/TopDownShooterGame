// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/TA_WeaponRangeBase.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATA_WeaponRangeBase::ATA_WeaponRangeBase()
{
	MuzzleComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->ArrowLength = 20.0f;
	MuzzleComponent->SetupAttachment(CustomRootComponent);
}

// Called when the game starts or when spawned
void ATA_WeaponRangeBase::BeginPlay()
{
	Super::BeginPlay();
}