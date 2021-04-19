// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TA_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/TA_WeaponBase.h"

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

}

void ATA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ActionWeapon", IE_Pressed, this, &ATA_Player::StartAction);
	PlayerInputComponent->BindAction("ActionWeapon", IE_Released, this, &ATA_Player::StopAction);
}

void ATA_Player::StartAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
}

void ATA_Player::StopAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop"));
}

void ATA_Player::AttachWeapon(ATA_WeaponBase* Weapon)
{
	if (IsValid(Weapon))
	{
		WeaponSelected = Weapon;
		WeaponRight->SetStaticMesh(Weapon->GetWeaponMesh());
	}
}

