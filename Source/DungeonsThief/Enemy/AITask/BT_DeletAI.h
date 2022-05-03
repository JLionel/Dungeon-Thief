// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsThief/Enemy/AITask/BT_BaseTaskDungeonsThief.h"
#include "BT_DeletAI.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_DeletAI : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type CodeToExecute() override;
};
