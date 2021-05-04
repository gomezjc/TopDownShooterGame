// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullet/TA_BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATA_BulletBase::ATA_BulletBase()
{
	PrimaryActorTick.bCanEverTick = false;
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	SetRootComponent(HitSphere);
	HitSphere->InitSphereRadius(12.0f);
	HitSphere->SetNotifyRigidBodyCollision(true);
	HitSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitSphere->SetNotifyRigidBodyCollision(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(HitSphere);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	if (GetOwner())
	{
		MeshComponent->IgnoreActorWhenMoving(GetOwner(), true);
		if (GetOwner()->GetOwner())
		{
			MeshComponent->IgnoreActorWhenMoving(GetOwner()->GetOwner(), true);
		}
	}
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->Velocity = FVector::ForwardVector;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ATA_BulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}


