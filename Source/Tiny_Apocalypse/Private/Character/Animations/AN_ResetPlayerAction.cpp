// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animations/AN_ResetPlayerAction.h"
#include "Player/TA_Player.h"

void UAN_ResetPlayerAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* PlayerActor = MeshComp->GetOwner();

	if (IsValid(PlayerActor))
	{
		ATA_Player* PlayerController = Cast<ATA_Player>(PlayerActor);

		if (IsValid(PlayerController))
		{
			PlayerController->SetAnimateRangeWeapon(false);
		}
	}
}
