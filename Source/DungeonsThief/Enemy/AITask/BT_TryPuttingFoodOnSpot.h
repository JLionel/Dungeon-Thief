// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseTaskDungeonsThief.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_TryPuttingFoodOnSpot.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_TryPuttingFoodOnSpot : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type CodeToExecute() override;
};
