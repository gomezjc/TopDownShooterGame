// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/TA_WeaponMeleeBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ATA_WeaponMeleeBase::ATA_WeaponMeleeBase()
{
	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	WeaponCollider->SetupAttachment(CustomRootComponent);
	WeaponCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	WeaponCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	WeaponCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ATA_WeaponMeleeBase::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ATA_WeaponMeleeBase::OnPlayerBeginOverlap);
	WeaponCollider->OnComponentEndOverlap.AddDynamic(this, &ATA_WeaponMeleeBase::OnPlayerEndOverlap);
}

void ATA_WeaponMeleeBase::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATA_WeaponMeleeBase::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
