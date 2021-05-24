// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums/ETA_ItemType.h"
#include "TA_ItemCollectable.generated.h"

UCLASS()
class TINY_APOCALYPSE_API ATA_ItemCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATA_ItemCollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")
	ETA_ItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	class UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	class UTextRenderComponent* TextRenderComponentQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
	FText CollectableName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")
	class USphereComponent* SphereComponent;
	
	UFUNCTION(BlueprintCallable, Category="Collectable")
	virtual void OnInteract(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Collectable")
	virtual void OnEndInteract(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="General")
	ETA_ItemType GetItemType() const { return ItemType; }
};
