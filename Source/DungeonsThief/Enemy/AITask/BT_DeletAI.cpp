// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_DeletAI.h"

#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

EBTNodeResult::Type UBT_DeletAI::CodeToExecute()
{
	ASpawnEnemyManager* SpawnEnemyManager = MyGameMode->GetSpawnManager();

	if (SpawnEnemyManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnEnemyManager not found"))
		return EBTNodeResult::Failed;
	}

	SpawnEnemyManager->DeleteAI(AICharacter);

	return EBTNodeResult::Succeeded;
}
