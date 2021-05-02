// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animations/AN_StartActionWeapon.h"
#include "Character/TA_CharacterBase.h"

void UAN_StartActionWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* PlayerActor = MeshComp->GetOwner();

	if (IsValid(PlayerActor))
	{
		ATA_CharacterBase* Character = Cast<ATA_CharacterBase>(PlayerActor);

		if (IsValid(Character))
		{
			Character->StartWeaponAction();
		}
	}
}
