// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/TA_ItemCollectable.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ATA_ItemCollectable::ATA_ItemCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollider"));
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(SphereComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Title"));
	TextRenderComponent->SetupAttachment(SphereComponent);
	TextRenderComponentQuantity = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Quantity Text"));
	TextRenderComponentQuantity->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ATA_ItemCollectable::BeginPlay()
{
	Super::BeginPlay();	
	TextRenderComponent->SetText(CollectableName);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATA_ItemCollectable::OnInteract);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATA_ItemCollectable::OnEndInteract);
}

void ATA_ItemCollectable::OnInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATA_ItemCollectable::OnEndInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ATA_ItemCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
} 

