// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Wandering UMETA(DisplayName = "Wandering"),
	EES_CarryFood UMETA(DisplayName = "CarryFood"),

	EES_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class DUNGEONSTHIEF_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AAIEnemyController();

	FORCEINLINE EEnemyState GetEnemyState() { return EnemyState; }
	FORCEINLINE void SetEnemyState(EEnemyState State) { EnemyState = State; }

	FORCEINLINE UBlackboardComponent* GetBlackBoardComponent() const { return BlackboardComponent; }

	FORCEINLINE class AAIEnemyCharacter* GetAICharacter() { return AICharacter; }

	FORCEINLINE float GetFieldOfView() { return FieldOfView; }
	FORCEINLINE float GetSightDistance() { return SightDistance; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	EEnemyState EnemyState;

	/* Reference to the Behavior Tree */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	/* BlackBoard reference */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBlackboardComponent* BlackboardComponent;

	/* Blackboard keys */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	class AAIEnemyCharacter* AICharacter;

	UPROPERTY(VisibleAnywhere, Category= "AI")
	float FieldOfView;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	float SightDistance;

	/* This function is called when the enemy is spawned */
	/* We'll initialize the blackboard and start the behaviour tree */
	virtual void OnPossess(APawn* InPawn) override;
};
