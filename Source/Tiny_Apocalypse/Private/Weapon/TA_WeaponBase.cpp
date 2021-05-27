// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_WeaponBase.h"


#include "Player/TA_Player.h"

// Sets default values
ATA_WeaponBase::ATA_WeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootcomponent"));
	RootComponent = CustomRootComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CustomRootComponent);
}

// Called when the game starts or when spawned
void ATA_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ATA_WeaponBase::IsPlayer(AActor* OtherActor)
{
	if (IsValid(OtherActor))
	{
		ATA_Player* OverlapCharacter = Cast<ATA_Player>(OtherActor);
		return IsValid(OverlapCharacter);
	}
	return false;
}

void ATA_WeaponBase::StartWeaponAction()
{
	BP_StartWeaponAction();
}

void ATA_WeaponBase::StopWeaponAction()
{
	BP_StopWeaponAction();
}

void ATA_WeaponBase::OnWeaponEquipped()
{
}

void ATA_WeaponBase::OnWeaponUnEquipped()
{
}
