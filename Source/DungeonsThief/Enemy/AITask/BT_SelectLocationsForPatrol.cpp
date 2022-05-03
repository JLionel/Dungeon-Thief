// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectLocationsForPatrol.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_SelectLocationsForPatrol::CodeToExecute()
{
	ASpawnEnemyManager* SpawnEnemyManager = MyGameMode->GetSpawnManager();

	if (SpawnEnemyManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodManager not found"))
		return EBTNodeResult::Failed;
	}

	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	FNavLocation RandPointOnNav;

	TArray<FVector> LocationsForPatrol;

	for (int i = 0; i < 2; i++)
	{
		do
		{
			NavSystem->GetRandomPoint(RandPointOnNav);
		}
		while (!NavSystem->ProjectPointToNavigation(RandPointOnNav.Location, RandPointOnNav));

		LocationsForPatrol.Add(RandPointOnNav.Location);
	}

	if (LocationsForPatrol.Num() == 2)
	{
		AICharacter->SetLocationsForPatrol(LocationsForPatrol);
		BlackboardComponent->SetValueAsInt("HasARole", 1);
		SpawnEnemyManager->SetGlobalWaitAI(false);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
