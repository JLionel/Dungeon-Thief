// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_GiveRole.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

EBTNodeResult::Type UBT_GiveRole::CodeToExecute()
{
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

	if (SpawnEnemyManager->GetGlobalWaitAI())
	{
		UE_LOG(LogTemp, Log, TEXT("Waiting %s"), *AICharacter->GetName())
		return EBTNodeResult::Failed;
	}

	SpawnEnemyManager->SetGlobalWaitAI(true);
	const int NumberOfFoodInWorld = FoodManager->GetAllFoodInWorld().Num();
	const int NumberOfSpotInWorld = FoodManager->GetAllSpotInGame().Num();

	MaxFoodInWorld = NumberOfSpotInWorld >= 5 ? 5 : NumberOfSpotInWorld;

	if (NumberOfFoodInWorld >= MaxFoodInWorld)
	{
		uint8 ByteEnum = static_cast<uint8>(EEnemyState::EES_Patrolling);
		BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
	}
	else
	{
		uint8 ByteEnum = static_cast<uint8>(EEnemyState::EES_CarryFood);
		BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
		AIController->SetEnemyState(EEnemyState::EES_CarryFood);
	}
	return EBTNodeResult::Succeeded;
}
