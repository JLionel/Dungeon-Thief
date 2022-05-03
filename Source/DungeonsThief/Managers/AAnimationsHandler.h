// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAnimationsHandler.generated.h"


/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AAnimationsHandler : public AActor
{
	GENERATED_BODY()

public:
	AAnimationsHandler();

	void PlayAnimation(class ACharacter* Character, class UAnimMontage* MontageToPlay);
};
