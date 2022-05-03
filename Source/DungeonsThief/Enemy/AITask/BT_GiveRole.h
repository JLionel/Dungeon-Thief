// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseTaskDungeonsThief.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_GiveRole.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_GiveRole : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type CodeToExecute() override;

	int MaxFoodInWorld;
};
