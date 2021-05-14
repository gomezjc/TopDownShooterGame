// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TA_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/TA_WeaponRangeBase.h"

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
	FightingWalkSpeed = DefaultWalkSpeed / 2;
}

void ATA_Player::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetMesh()))
	{
		AnimInstance = GetMesh()->GetAnimInstance();
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


void ATA_Player::OnWeaponAction()
{
	SetAnimateRangeWeapon(true);
}

void ATA_Player::StartAction()
{
	if(WeaponSelected && !bIsReloading)
	{
		bIsAttacking = true;
		GetCharacterMovement()->MaxWalkSpeed = FightingWalkSpeed;
		WeaponSelected->StartWeaponAction();
	}
}

void ATA_Player::StopAction()
{
	if (WeaponSelected)
	{
		bIsAttacking = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
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
	UE_LOG(LogTemp, Warning, TEXT("OnReloadComplete"))
	bIsReloading = false;
}

void ATA_Player::Roll()
{
	UE_LOG(LogTemp, Warning, TEXT("Rolling"))
}

void ATA_Player::Reload()
{
	if (WeaponNeedReload())
	{
		UE_LOG(LogTemp, Warning, TEXT("Reloading"))
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

