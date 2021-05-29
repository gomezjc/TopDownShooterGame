// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/TA_WeaponRangeBase.h"
#include "Components/ArrowComponent.h"
#include "Inventory/TA_ItemBullet.h"
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

void ATA_WeaponRangeBase::OnWeaponEquipped()
{
	Super::OnWeaponEquipped();
	ValidateMagazineInventory();
}

void ATA_WeaponRangeBase::OnWeaponUnEquipped()
{
	Super::OnWeaponUnEquipped();
}

void ATA_WeaponRangeBase::NotifyReloadComplete()
{
	BP_ReloadComplete();
	SetMagazineWeapon();
}

void ATA_WeaponRangeBase::FireRound()
{
	if (CurrentBullets > 0)
	{
		CurrentBullets--;
		if (IsValid(BulletWeapon))
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD_WEAPON: ADD RANGE %d"), CurrentBullets);
			BulletWeapon->SetMagazineWeapon(CurrentBullets);
		}
		AActor* BulletOwner = GetOwner() ? GetOwner() : this;
		const FTransform SpawnTransform = MuzzleComponent->GetComponentTransform();
		FActorSpawnParameters Params;
		Params.Owner = BulletOwner;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ATA_BulletBase>(BulletClass, SpawnTransform, Params);
		BP_FireRound();
		NotifyOwner();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AMMO"));
	}
}

void ATA_WeaponRangeBase::NotifyOwner()
{
	ATA_Player* Player = GetPlayer();
	if (IsValid(Player))
	{
		Player->OnWeaponAction(CurrentBullets, RecoilForcePercentage);
	}
}

void ATA_WeaponRangeBase::SetMagazineWeapon()
{
	if (IsValid(BulletWeapon))
	{
		BulletWeapon->SetMagazineWeapon(CurrentBullets);
		CurrentBullets = BulletWeapon->ReloadMagazine(MagazineCapacity);
	}
}

ATA_Player* ATA_WeaponRangeBase::GetPlayer()
{
	if (GetOwner())
	{
		ATA_Player* Player = Cast<ATA_Player>(GetOwner());
		if (IsValid(Player))
		{
			return Player;
		}
	}
	return nullptr;
}

void ATA_WeaponRangeBase::ValidateMagazineInventory()
{
	BulletWeapon = GetBulletsFromInventory();
	if (IsValid(BulletWeapon))
	{
		CurrentBullets = BulletWeapon->GetMagazineWeapon();
	}
}

UTA_ItemBullet* ATA_WeaponRangeBase::GetBulletsFromInventory()
{
	ATA_Player* Player = GetPlayer();
	UTA_ItemBullet* Bullet = nullptr;
	if (IsValid(Player))
	{
		 Bullet = Player->GetBulletByType(BulletUsed);
	}
	return Bullet;
}
