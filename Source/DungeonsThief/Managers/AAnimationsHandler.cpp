// Fill out your copyright notice in the Description page of Project Settings.

#include "AAnimationsHandler.h"
#include "GameFramework/Character.h"

AAnimationsHandler::AAnimationsHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimationsHandler::PlayAnimation(ACharacter* Character, UAnimMontage* MontageToPlay)
{
	if (Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (AnimInstance && MontageToPlay)
		{
			AnimInstance->Montage_Play(MontageToPlay, 1.0f);
		}
	}
}
