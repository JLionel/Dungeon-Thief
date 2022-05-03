// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseTaskDungeonsThief.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_UpdatePlayerDirection.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_UpdatePlayerDirection : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()

protected:
	/* Execute this function each time this Task is going to fire */
	virtual EBTNodeResult::Type CodeToExecute() override;
};
