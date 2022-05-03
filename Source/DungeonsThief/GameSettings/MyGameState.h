// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

UENUM(BlueprintType)
enum class EGameplayMode : uint8
{
	EGM_NormalMode UMETA(DisplayName = "NormalMode"),
	EGM_ScoreMode UMETA(DisplayName = "ScoreMode")
};

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMyGameState : public AGameState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Helpers")
	TSubclassOf<class ASpawnEnemyManager> SpawnEnemyManageBlueprint;

	TArray<class AAIEnemyCharacter*> EnemiesInLevel;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	int PlayerPoints;

	UPROPERTY(EditAnywhere, Category = "Game State")
	int MaxPoints = 5;

public:
	FORCEINLINE int GetPlayerPoints() { return PlayerPoints; }
	FORCEINLINE void AddPlayerPoints(int PointsToAdd) { PlayerPoints += PointsToAdd; }

	FORCEINLINE float GetProgressionPercent()
	{
		return static_cast<float>(PlayerPoints) / static_cast<float>(MaxPoints);
	}

	FORCEINLINE TArray<class AAIEnemyCharacter*> GetEnemiesInLevel() { return EnemiesInLevel; }
	FORCEINLINE void AddEnemiesInLevel(class AAIEnemyCharacter* EnemyToAdd) { EnemiesInLevel.Add(EnemyToAdd); }

	FORCEINLINE bool HasPlayerWin() { return PlayerPoints >= MaxPoints; }

	class ASpawnEnemyManager* SpawnEnemyManager();
};
