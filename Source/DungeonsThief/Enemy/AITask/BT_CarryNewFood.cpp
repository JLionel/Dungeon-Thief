// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_CarryNewFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

EBTNodeResult::Type UBT_CarryNewFood::CodeToExecute()
{
	//get FoodManager
	AFoodManager* FoodManager = MyGameMode->GetFoodManager();
	ASpawnEnemyManager* SpawnEnemyManager = MyGameMode->GetSpawnManager();

	if (FoodManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodManager not found"))
		return EBTNodeResult::Failed;
	}

	if (SpawnEnemyManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnEnemyManager not found"))
		return EBTNodeResult::Failed;
	}

	//spawn food on the AICharacter
	AActor* FoodToCarry = FoodManager->SpawnFood(AICharacter->GetActorLocation());

	if (FoodToCarry == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodToCarry not spawned"))
		return EBTNodeResult::Failed;
	}

	//Then let him Carry the food
	AICharacter->SetNearFoodActor(FoodToCarry);
	AICharacter->InteractWithItem();
	SpawnEnemyManager->SetGlobalWaitAI(false);
	BlackboardComponent->SetValueAsObject("FoodCarrying", FoodToCarry);
	BlackboardComponent->SetValueAsInt("HasARole", 1);
	return EBTNodeResult::Succeeded;
}
