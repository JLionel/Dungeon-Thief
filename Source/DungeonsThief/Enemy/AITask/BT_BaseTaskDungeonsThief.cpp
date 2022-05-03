// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_BaseTaskDungeonsThief.h"

#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"

EBTNodeResult::Type UBT_BaseTaskDungeonsThief::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return EBTNodeResult::Failed;
	}

	AICharacter = AIController->GetAICharacter();
	if (AICharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AICharacter is null"));
		return EBTNodeResult::Failed;
	}

	BlackboardComponent = AIController->GetBlackBoardComponent();
	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null"));
		return EBTNodeResult::Failed;
	}

	return CodeToExecute();
}

EBTNodeResult::Type UBT_BaseTaskDungeonsThief::CodeToExecute()
{
	return EBTNodeResult::Failed;
}

AFoodSpot* UBT_BaseTaskDungeonsThief::SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList)
{
	//remove 0.01 to avoid a crash and keep the same chance for each index
	const int ActorIndex = FMath::FRandRange(0, ActorList.Num() - 0.01f);
	return ActorList[ActorIndex];
}
