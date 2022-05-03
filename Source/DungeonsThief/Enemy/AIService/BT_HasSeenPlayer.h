// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseServiceDungeonThief.h"
#include "BT_HasSeenPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_HasSeenPlayer : public UBT_BaseServiceDungeonThief
{
	GENERATED_BODY()

protected:
	virtual void CodeToExecute() override;

	bool CanSeePlayerRayCast(FVector ForwardVector, FVector StartTrace, float MaxDistance, class AActor* IgnoreActor);
};
