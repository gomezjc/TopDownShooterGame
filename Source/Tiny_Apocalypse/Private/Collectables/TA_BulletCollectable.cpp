// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/TA_BulletCollectable.h"

#include "Components/TextRenderComponent.h"
#include "Inventory/TA_ItemBullet.h"
#include "Player/TA_Player.h"

ATA_BulletCollectable::ATA_BulletCollectable()
{
	ItemType = ETA_ItemType::ItemType_Bullet;
}

void ATA_BulletCollectable::BeginPlay()
{
	Super::BeginPlay();
	TextRenderComponentQuantity->SetText(FText::AsNumber(QuantityToPick));
}

void ATA_BulletCollectable::OnInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATA_Player* Player = Cast<ATA_Player>(OtherActor);
	if (IsValid(Player))
	{
		UTA_ItemBullet* ItemToAdd = NewObject<UTA_ItemBullet>();
		ItemToAdd->SetQuantity(QuantityToPick);
		ItemToAdd->SetBulletType(BulletType);
		Player->AddItemToInventory(ItemToAdd);
		Destroy(); // TODO: Let the rest of bullets available to pick and don't destroy on this scenario.
	}
}

void ATA_BulletCollectable::OnEndInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Interact"));
}
