// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TA_WeaponBase.h"
#include "Components/BoxComponent.h"
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

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	WeaponCollider->SetupAttachment(CustomRootComponent);
	WeaponCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	WeaponCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	WeaponCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ATA_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ATA_WeaponBase::OnPlayerBeginOverlap);
	WeaponCollider->OnComponentEndOverlap.AddDynamic(this, &ATA_WeaponBase::OnPlayerEndOverlap);
}

void ATA_WeaponBase::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATA_WeaponBase::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
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

void ATA_WeaponBase::PickUpWeapon()
{
}

