// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/TA_WeaponRangeBase.h"
#include "Components/ArrowComponent.h"
#include "Player/TA_Player.h"
#include "Weapon/Bullet/TA_BulletBase.h"

// Sets default values
ATA_WeaponRangeBase::ATA_WeaponRangeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MuzzleComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->ArrowLength = 20.0f;
	MuzzleComponent->SetupAttachment(CustomRootComponent);
}

// Called when the game starts or when spawned
void ATA_WeaponRangeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATA_WeaponRangeBase::Tick(float DeltaSeconds)
{
	if (bCanShoot && FireCountdown <= 0)
	{
		FireRound();
		FireCountdown = 1.0f * FireRate;
	}
	FireCountdown -= DeltaSeconds;
}

void ATA_WeaponRangeBase::StartWeaponAction()
{
	Super::StartWeaponAction();
	bCanShoot = true;
}

void ATA_WeaponRangeBase::StopWeaponAction()
{
	Super::StopWeaponAction();
	bCanShoot = false;
}

void ATA_WeaponRangeBase::FireRound()
{
	AActor* BulletOwner = GetOwner() ? GetOwner() : this;
	const FTransform SpawnTransform = MuzzleComponent->GetComponentTransform();
	FActorSpawnParameters Params;
	Params.Owner = BulletOwner;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ATA_BulletBase>(BulletClass, SpawnTransform, Params);
	BP_FireRound();
	NotifyOwner();
}

void ATA_WeaponRangeBase::NotifyOwner()
{
	if (GetOwner())
	{
		ATA_Player* Player = Cast<ATA_Player>(GetOwner());
		if(IsValid(Player))
		{
			Player->OnWeaponAction();
		}
	}
}

