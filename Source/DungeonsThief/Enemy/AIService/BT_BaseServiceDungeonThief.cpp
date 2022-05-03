// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AIService/BT_BaseServiceDungeonThief.h"

#include "DungeonsThief/Enemy/AIEnemyController.h"

void UBT_BaseServiceDungeonThief::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);

	AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not found in BaseService"))
		return;
	}

	BlackboardComponent = AIController->GetBlackBoardComponent();
	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent not found in BaseService"))
		return;
	}

	AICharacter = AIController->GetAICharacter();
	if (AICharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AICharacter not found in BaseService"))
		return;
	}

	CodeToExecute();
}
