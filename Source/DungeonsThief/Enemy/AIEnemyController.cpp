// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyController.h"
#include "AIEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

/*
 * Contructor of the class
 */
AAIEnemyController::AAIEnemyController()
{
	EnemyState = EEnemyState::EES_Patrolling;

	//Initialize BehaviourTreeComponent and BlackBoardComponent and keys
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	LocationToGoKey = "LocationToGo";

	FieldOfView = 67.5f;

	SightDistance = 1000.f;
}

void AAIEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<AAIEnemyCharacter>(InPawn);

	if (AICharacter)
	{
		//If the blackboard variable is valid, we initialize the current blackBoard of the behaviour tree
		if (AICharacter->BehaviourTree->BlackboardAsset)
		{
			if (BlackboardComponent)
			{
				BlackboardComponent->InitializeBlackboard(*(AICharacter->BehaviourTree->BlackboardAsset));
			}
		}

		//Start the behaviour tree which coreesponds to the specific character
		BehaviorTreeComponent->StartTree(*AICharacter->BehaviourTree);
	}
}
