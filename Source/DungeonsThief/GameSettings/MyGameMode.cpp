// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyGameMode.h"

#include "MyGameInstance.h"
#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

void AMyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

void AMyGameMode::InitGameState()
{
	Super::InitGameState();

	AMyGameState* CurrentGameState = GetGameState<AMyGameState>();
	if (CurrentGameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentGameState is null"));
		return;
	}

	UWorld* World = GetWorld();
	if (World == nullptr && CurrentGameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("World or GameState are null"));
		return;
	}

	MyGameState = CurrentGameState;
}

void AMyGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
	if (MyGameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameState is null"));
		return;
	}
	
	SpawnEnemyManager = MyGameState->SpawnEnemyManager();
}

void AMyGameMode::WinGame()
{	
	if (MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance is null"));
		return;
	}
	
	MyGameInstance->AddPlayerXP(25 * XPBoostBuff);

	if (OnGameWin.IsBound())
	{
		OnGameWin.Broadcast();
	}
}

void AMyGameMode::LoseGame()
{
	if (OnGameLose.IsBound())
	{
		OnGameLose.Broadcast();
	}
}

void AMyGameMode::GainPoints(int Points)
{
	if (MyGameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameState is null"));
		return;
	}
	
	MyGameState->AddPlayerPoints(Points);

	if (OnGainPoints.IsBound())
	{
		OnGainPoints.Broadcast();
	}

	if (MyGameInstance != nullptr && MyGameState->HasPlayerWin() && MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_NormalMode)
	{
		WinGame();
	}
}
