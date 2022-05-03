// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_NextPatrolSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_NextPatrolSpot::CodeToExecute()
{
	AICharacter->RemoveFirstLocationForPatrol();

	return EBTNodeResult::Succeeded;
}
