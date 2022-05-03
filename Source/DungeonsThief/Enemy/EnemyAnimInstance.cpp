// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "AIEnemyCharacter.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		EnemyCharacter = Cast<AAIEnemyCharacter>(Pawn);
	}
}

void UEnemyAnimInstance::UpdateAnimationProperties()
{
	if (EnemyCharacter)
	{
		MovementSpeed = GetCharacterMovementSpeed();
		IsCarryItem = EnemyCharacter->GetIsCarryFood();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperties();
}

float UEnemyAnimInstance::GetCharacterMovementSpeed()
{
	if (EnemyCharacter)
	{
		FVector Speed = EnemyCharacter->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		return LateralSpeed.Size();
	}

	return 0;
}
