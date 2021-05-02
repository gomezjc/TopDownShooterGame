// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/TA_WeaponRangeBase.h"
#include "Components/ArrowComponent.h"
#include "Weapon/Bullet/TA_BulletBase.h"

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

void ATA_WeaponRangeBase::StartWeaponAction()
{
	Super::StartWeaponAction();
	AActor* BulletOwner = GetOwner() ? GetOwner() : this;
	const FTransform SpawnTransform = MuzzleComponent->GetComponentTransform();

	FActorSpawnParameters Params;
	Params.Owner = BulletOwner;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ATA_BulletBase>(BulletClass, SpawnTransform, Params);
}
