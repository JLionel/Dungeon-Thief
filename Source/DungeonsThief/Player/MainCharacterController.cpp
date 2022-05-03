// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Player/MainCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/HUD/UI_MenuEndGame.h"
#include "Kismet/GameplayStatics.h"


AMainCharacterController::AMainCharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();
	AMyGameMode* GameModeBase = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
	if (GameModeBase == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeBase is null"));
		return;
	}

	MyGameState = GameModeBase->GetGameState<AMyGameState>();
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance is null"));
		return;
	}

	if (GetPawn())
	{
		MyGameInstance->SetMainPlayerPawn(GetPawn());
	}

	if (WMain)
	{
		MainWidget = CreateWidget<UUserWidget>(this, WMain);
		MainWidget->AddToViewport();
		MainWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WCharacterPick)
	{
		CharacterPickWidget = CreateWidget<UUserWidget>(this, WCharacterPick);
		CharacterPickWidget->AddToViewport();
		CharacterPickWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WWinScreen)
	{
		WinScreenWidget = CreateWidget<UUserWidget>(this, WWinScreen);
		if (WinScreenWidget)
		{
			WinScreenWidget->AddToViewport();
			WinScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WLoseScreen)
	{
		LoseScreenWidget = CreateWidget<UUserWidget>(this, WLoseScreen);
		if (LoseScreenWidget)
		{
			LoseScreenWidget->AddToViewport();
			LoseScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WPauseMenu)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	bShowMouseCursor = true;
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainCharacterController::ShowWinScreen(bool Visibility)
{
	WinScreenWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	bShowMouseCursor = Visibility;
}

void AMainCharacterController::ShowLoseScreen(bool Visibility)
{
	UUI_MenuEndGame* LoseScreenCast = Cast<UUI_MenuEndGame>(LoseScreenWidget);
	
	if (LoseScreenCast == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LoseScreenCast is null"));
		return;
	}
	
	if (MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_ScoreMode)
	{
		LoseScreenCast->SetTextScore(MyGameState->GetPlayerPoints());
	}

	LoseScreenCast->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	bShowMouseCursor = Visibility;
}

void AMainCharacterController::ShowPauseMenu(bool Visibility)
{

	if(CanPause)
	{
		PauseMenuWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}


void AMainCharacterController::ShowMainMenu(bool Visibility)
{
	MainWidget->SetVisibility(Visibility? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AMainCharacterController::SetCanPause(bool state)
{
	CanPause = state;
}
