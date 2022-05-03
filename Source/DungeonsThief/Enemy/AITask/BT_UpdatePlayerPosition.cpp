// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_UpdatePlayerPosition.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_UpdatePlayerPosition::CodeToExecute()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		AMainCharacter* PlayerLocation = Cast<AMainCharacter>(PlayerPawn);

		if (PlayerLocation && AICharacter->GetHasSeenPlayer())
		{
			BlackboardComponent->SetValueAsVector("PlayerLocation", PlayerLocation->GetActorLocation());

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
