// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/GameSettings/MyGameState.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"


class AMyGameMode;

void UUI_MainClass::NativeConstruct()
{
	Super::NativeConstruct();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		return;
	}

	MyGameState = MyGameMode->GetGameState<AMyGameState>();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance == nullptr)
	{
		return;
	}

	if (MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_ScoreMode)
	{
		ScorePoint->SetVisibility(ESlateVisibility::Visible);
		FoodBar->SetPercent(1.0f);
	}
	else
	{
		ScorePoint->SetVisibility(ESlateVisibility::Hidden);
		FoodBar->SetPercent(0.0f);
	}

	MyGameMode->OnGainPoints.AddDynamic(this, &UUI_MainClass::UpdateProgression);
}

void UUI_MainClass::UpdateProgression()
{
	if (MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameInstance null"));
		return;
	}

	if (MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_NormalMode)
	{
		if (MyGameState == nullptr)
		{
			return;
		}
		
		FoodBar->SetPercent(MyGameState->GetProgressionPercent()); //Set progress bar value
	}
	else
	{
		if (MyGameState == nullptr)
		{
			return;
		}
		
		ScorePoint->SetText(FText::AsNumber(MyGameState->GetPlayerPoints()));
	}
}
