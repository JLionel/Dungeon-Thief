// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	virtual void NativeInitializeAnimation() override;

	void UpdateAnimationProperties();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties")
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties")
	bool IsCarryItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties")
	bool IsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties")
	int CharacterNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AMainCharacter* MainCharacter;
};
