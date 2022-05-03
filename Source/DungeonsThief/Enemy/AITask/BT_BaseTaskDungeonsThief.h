// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_BaseTaskDungeonsThief.generated.h"

/**
 * Base class for Task Node on DungeonsThief project
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_BaseTaskDungeonsThief : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	/* Execute this function each time this Task is going to fire */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	class AAIEnemyController* AIController;
	class AAIEnemyCharacter* AICharacter;

	UBlackboardComponent* BlackboardComponent;

	class AMyGameMode* MyGameMode;

	virtual EBTNodeResult::Type CodeToExecute();

	class AFoodSpot* SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList);
};
