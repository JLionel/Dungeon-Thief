// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

ASpawnEnemyManager* AMyGameState::SpawnEnemyManager()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return nullptr;
	}

	//Location used in the MAIN LEVEL
	FVector SpawnLocation = FVector(-4840, -11410, 970);
	FRotator SpawnRotation = FRotator(0, -90, 0);

	if (World->GetName() == FString("ForgeLevel"))
	{
		SpawnLocation = FVector(357, -24802, -1291);
		SpawnRotation = FRotator(0, -180, 0);
	}
	return World->SpawnActor<ASpawnEnemyManager>(SpawnEnemyManageBlueprint, SpawnLocation, SpawnRotation);
}
