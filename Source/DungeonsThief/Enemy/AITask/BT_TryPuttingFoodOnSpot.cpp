// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_TryPuttingFoodOnSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"

EBTNodeResult::Type UBT_TryPuttingFoodOnSpot::CodeToExecute()
{
	AICharacter->InteractWithItem();

	if (AICharacter->GetFoodCarried() != nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AFood* FoodDroped = Cast<AFood>(AICharacter->GetPlayerNearFoodActor());

	if (FoodDroped == nullptr)
	{
		return EBTNodeResult::Failed;

	}
	if (FoodDroped->GetIsOnSpot())
	{
		BlackboardComponent->ClearValue("FoodCarrying");
		BlackboardComponent->ClearValue("SpotLocationToGo");
		return EBTNodeResult::Succeeded;
	}
	AFoodSpot* SpotVisited = Cast<AFoodSpot>(BlackboardComponent->GetValueAsObject("SpotLocationToGo"));

	if (SpotVisited == nullptr)
	{
		return EBTNodeResult::Failed;

	}
	
	BlackboardComponent->ClearValue("SpotLocationToGo");
	AICharacter->AddAlreadyVisitedSpot(SpotVisited);
	AICharacter->InteractWithItem();

	return EBTNodeResult::Failed;
}
