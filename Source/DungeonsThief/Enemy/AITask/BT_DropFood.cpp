// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_DropFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"

EBTNodeResult::Type UBT_DropFood::CodeToExecute()
{
	AFood* StoreFood = Cast<AFood>(BlackboardComponent->GetValueAsObject("FoodCarrying"));

	if (StoreFood == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodCarrying not found"))
		return EBTNodeResult::Failed;
	}

	AICharacter->DropItem();

	BlackboardComponent->SetValueAsObject("FoodDropped", StoreFood);
	BlackboardComponent->SetValueAsVector("FoodDroppedLocation", StoreFood->GetActorLocation());
	BlackboardComponent->ClearValue("FoodCarrying");
	return EBTNodeResult::Succeeded;
}
