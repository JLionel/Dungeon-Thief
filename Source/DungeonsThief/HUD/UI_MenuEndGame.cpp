// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MenuEndGame.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/GameSettings/MySaveGame.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/GameSettings/MySaveGame.h"
#include "Kismet/GameplayStatics.h"


void UUI_MenuEndGame::NativeConstruct()
{
	Super::NativeConstruct();

	BtnPlayAgain->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::RestartGame);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::ReturnToMenu);
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if(MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance is null"));
		return;
	}

	if (bLoseUI && MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_ScoreMode)
	{
		EndScore->SetVisibility(ESlateVisibility::Visible);
		EndBestScore->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		EndScore->SetVisibility(ESlateVisibility::Hidden);
		EndBestScore->SetVisibility(ESlateVisibility::Hidden);
	}

	MainLevelName = FName(GetWorld()->GetName());

	//Bind method with the GameMode
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}

	MyGameMode->OnGameWin.AddDynamic(this, &UUI_MenuEndGame::UpdateXPProgression);
	MyGameMode->OnGameLose.AddDynamic(this, &UUI_MenuEndGame::UpdateXPProgression);
}

void UUI_MenuEndGame::RestartGame()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, MainLevelName);
	}
}

void UUI_MenuEndGame::ReturnToMenu()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, MainMenuLevelName);
	}
}


void UUI_MenuEndGame::SetTextScore(int Score)
{
	int SavedScore = MyGameInstance->GetBestScore();

    UpdateXPProgression();
    
	EndScore->SetText(FText::Format(FText::FromString("Your score : {0}"), Score));

	if (Score > SavedScore)
	{
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), Score));

		//Call score system of the game instance
		MyGameInstance->SetBestScore(Score);
	}
	else
	{
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), SavedScore));
	}

	MyGameInstance->AddPlayerXP(Score * 4);
}


/**
 * @brief Update the XP progress bar value
 */
void UUI_MenuEndGame::UpdateXPProgression()
{
	if (MyGameInstance == nullptr)
	{
		return;
	}

	float Percent = static_cast<float>(MyGameInstance->GetPlayerXP()) / static_cast<float>(100);
	XPBar->SetPercent(Percent); //Set progress bar value

	PlayerLevel->SetText(FText::Format(FText::FromString("{0}"), MyGameInstance->GetPlayerXPLevel()));
}
