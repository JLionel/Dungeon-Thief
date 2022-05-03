// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseServiceDungeonThief.h"
#include "BT_SelectSpotIfPatrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_SelectSpotIfPatrol : public UBT_BaseServiceDungeonThief
{
	GENERATED_BODY()
protected:
	virtual void CodeToExecute() override;
};
