// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TA_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/TA_WeaponRangeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Inventory/TA_ItemBullet.h"
#include "Math/Vector.h"

ATA_Player::ATA_Player()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	RollTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLineRoll"));
	RecoilTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("RecoilTimeLine"));

	InterpolationRoll.BindUFunction(this, FName("TimelineRollFloatReturn"));
	RollTimelineFinish.BindUFunction(this, FName("OnTimelineRollFinished"));

	InterpolationRecoil.BindUFunction(this, FName("TimelineRecoilFloatReturn"));
	RecoilTimelineFinish.BindUFunction(this, FName("OnTimelineRecoilFinished"));

	bIsReloading = false;
	bIsRolling = false;
}

void ATA_Player::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetMesh()))
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}

	if (FRollingCurve)
	{	
		RollTimeline->AddInterpFloat(FRollingCurve, InterpolationRoll, FName("Alpha"));
		RollTimeline->SetTimelineFinishedFunc(RollTimelineFinish);
	}

	if (FRecoilCurve)
	{	
		RecoilTimeLine->AddInterpFloat(FRecoilCurve, InterpolationRecoil, FName("Alpha"));
		RecoilTimeLine->SetTimelineFinishedFunc(RecoilTimelineFinish);
	}
}

void ATA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ActionWeapon", IE_Pressed, this, &ATA_Player::StartAction);
	PlayerInputComponent->BindAction("ActionWeapon", IE_Released, this, &ATA_Player::StopAction);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATA_Player::Reload);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ATA_Player::Roll);
}

void ATA_Player::EquipWeapon(TSubclassOf<ATA_WeaponBase> WeaponClass)
{
	if (WeaponSelected)
	{
		UnEquipWeapon();
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	WeaponSelected = GetWorld()->SpawnActor<ATA_WeaponBase>(WeaponClass, Params);
	WeaponSelected->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketWeapon);
	WeaponSelected->OnWeaponEquipped();
	OnWeaponChangeDelegate.Broadcast(WeaponSelected);
}

void ATA_Player::UnEquipWeapon()
{
	if (WeaponSelected)
	{
		WeaponSelected->Destroy();
		WeaponSelected->OnWeaponUnEquipped();
	}
}

void ATA_Player::OnWeaponRangeAction(int32 CurrentBullets, float RecoilPercentage)
{
	SetAnimateRangeWeapon(true);
	OnWeaponShootDelegate.Broadcast(CurrentBullets);
	RecoilWalkSpeed = DefaultWalkSpeed * RecoilPercentage;
	GetCharacterMovement()->MaxWalkSpeed = RecoilWalkSpeed;
	RecoilTimeLine->SetLooping(false);
	RecoilTimeLine->SetIgnoreTimeDilation(true);
	RecoilTimeLine->PlayFromStart();
}

void ATA_Player::StartAction()
{
	if(WeaponSelected && !bIsReloading && !bIsRolling)
	{
		bIsAttacking = true;
		WeaponSelected->StartWeaponAction();
	}
}

void ATA_Player::StopAction()
{
	if (WeaponSelected)
	{
		bIsAttacking = false;
		WeaponSelected->StopWeaponAction();
		SetAnimateRangeWeapon(false);
	}
}

void ATA_Player::SetAnimateRangeWeapon(bool Value)
{
	bAnimateRangeWeapon = Value;
}

void ATA_Player::OnReloadComplete()
{
	bIsReloading = false;
	OnWeaponChangeDelegate.Broadcast(WeaponSelected);
}

void ATA_Player::Roll()
{
	if (!bIsRolling && !GetCharacterMovement()->IsFalling())
	{
		StopAction();
		bIsRolling = true;
		CurrentRollPosition = GetCapsuleComponent()->GetComponentLocation();
		DestinationRollPosition = GetActorForwardVector() * RollSpeed;
		AnimInstance->Montage_Play(RollMontage);
		DisablePlayerMovement();
		RollTimeline->SetLooping(false);
		RollTimeline->SetIgnoreTimeDilation(true);
		RollTimeline->PlayFromStart();
	}
}

void ATA_Player::Reload()
{
	if (WeaponNeedReload())
	{
		ATA_WeaponRangeBase* WeaponRangeSelected = Cast<ATA_WeaponRangeBase>(WeaponSelected);
		if (IsValid(AnimInstance) && IsValid(WeaponRangeSelected))
		{
			bIsReloading = true;
			StopAction();
			UAnimMontage* ReloadMontage = WeaponRangeSelected->GetReloadMontage();
			const float ReloadMontageDuration = AnimInstance->Montage_Play(ReloadMontage);
			GetWorld()->GetTimerManager().SetTimer(TimeHandle_Reload, this, &ATA_Player::OnReloadComplete, ReloadMontageDuration, false);
		}
	}
}

bool ATA_Player::WeaponNeedReload()
{
	bool IsRangeWeapon = false;
	if (WeaponSelected)
	{
		ATA_WeaponRangeBase* WeaponRangeSelected = Cast<ATA_WeaponRangeBase>(WeaponSelected);
		IsRangeWeapon = IsValid(WeaponRangeSelected);
	}
	
	return IsRangeWeapon;
}

void ATA_Player::DisablePlayerMovement()
{
	GetCharacterMovement()->DisableMovement();
}

void ATA_Player::RecoverPlayerMovement()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	GetCharacterMovement()->SetDefaultMovementMode();
}

void ATA_Player::AddItemToInventory(UTA_ItemInventory* ItemInventory)
{
	UTA_ItemBullet* ItemBulletInventory = Cast<UTA_ItemBullet>(ItemInventory);
	if(IsValid(ItemBulletInventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is a Bullet"));
		UTA_ItemBullet* CurrentBulletInventory = GetBulletByType(ItemBulletInventory->GetBulletType());
		if (IsValid(CurrentBulletInventory))
		{
			CurrentBulletInventory->SetQuantity(CurrentBulletInventory->GetQuantity() + ItemBulletInventory->GetQuantity());
		}else
		{
			InventoryData.Add(ItemInventory);
		}
	}
	
	if(WeaponSelected)
	{
		WeaponSelected->OnWeaponEquipped();
		OnWeaponChangeDelegate.Broadcast(WeaponSelected);
	}
}

UTA_ItemBullet* ATA_Player::GetBulletByType(ETA_BulletType BulletType)
{
	TArray<UTA_ItemInventory*> Bullets = InventoryData.FilterByPredicate([](const UTA_ItemInventory* Item){
		return Item->GetItemType() == ETA_ItemType::ItemType_Bullet;
	});
	UTA_ItemBullet* BulletSelected = nullptr;
	for(UTA_ItemInventory* ItemBullet : Bullets)
	{
		UTA_ItemBullet* BulletObj = Cast<UTA_ItemBullet>(ItemBullet);
		if (IsValid(BulletObj) && BulletObj->GetBulletType() == BulletType)
		{
			BulletSelected = BulletObj;
			break;
		}
	}
	return BulletSelected;
}

void ATA_Player::TimelineRollFloatReturn(float Value)
{
	GetCapsuleComponent()->SetRelativeLocationAndRotation(
		FMath::Lerp(CurrentRollPosition, CurrentRollPosition + DestinationRollPosition, Value),
		GetCapsuleComponent()->GetComponentRotation(), true);
}

void ATA_Player::OnTimelineRollFinished()
{
	bIsRolling = false;
	RollTimeline->Stop();
	RecoverPlayerMovement();
}

void ATA_Player::TimelineRecoilFloatReturn(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(
		RecoilWalkSpeed, DefaultWalkSpeed, Value, 1.0f);
}

void ATA_Player::OnTimelineRecoilFinished()
{
	
}
