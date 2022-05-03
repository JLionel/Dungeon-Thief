// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsThief/Enemy/AITask/BT_BaseTaskDungeonsThief.h"
#include "BT_PickBackDroppedFood.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_PickBackDroppedFood : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type CodeToExecute() override;
};
