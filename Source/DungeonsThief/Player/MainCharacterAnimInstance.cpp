// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn != nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(Pawn);
	}
}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	if (MainCharacter != nullptr)
	{
		FVector Velocity = MainCharacter->GetVelocity();
		FVector LateralVelocity = FVector(Velocity.X, Velocity.Y, 0.0f);

		MovementSpeed = LateralVelocity.Size();

		CharacterNum = MainCharacter->GetCharacterID();
		IsCarryItem = MainCharacter->GetIsCarryFood();
		IsCrouching = MainCharacter->GetIsCrouching();
	}
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperties();
}
