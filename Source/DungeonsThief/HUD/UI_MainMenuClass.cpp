// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainMenuClass.h"

#include "MainMenuController.h"
#include "Components/Button.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


class AMainMenuController;

void UUI_MainMenuClass::NativeConstruct()
{
	Super::NativeConstruct();


	BtnPlay->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::PlayNormalGame);
	BtnPlayScore->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::PlayScoreGame);
	BtnSettings->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::OpenSettings);
	BtnTutorial->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::OpenTutorial);
	BtnShop->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::OpenShop);
	BtnExit->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::ExitGame);

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUI_MainMenuClass::PlayNormalGame()
{
	UE_LOG(LogTemp, Warning, TEXT("START NORMAL GAME"));
	PlayGame(EGameplayMode::EGM_NormalMode);
}

void UUI_MainMenuClass::PlayScoreGame()
{
	UE_LOG(LogTemp, Warning, TEXT("START SCORE GAME"));
	PlayGame(EGameplayMode::EGM_ScoreMode);
}

void UUI_MainMenuClass::PlayGame(EGameplayMode GameplayMode)
{
	UWorld* World = GetWorld();

	if (World)
	{
		AMainMenuController* MenuController = Cast<AMainMenuController>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (MenuController != nullptr)
		{
			if (MyGameInstance)
			{
				MyGameInstance->SetGameplayMode(GameplayMode);
			}

			MenuController->ShowPickLevelMenu();
		}
	}
}


void UUI_MainMenuClass::OpenSettings()
{
	AMainMenuController* MenuController = Cast<AMainMenuController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MenuController != nullptr)
	{
		MenuController->ShowSettingsMenu();
	}
}

void UUI_MainMenuClass::OpenTutorial()
{
	AMainMenuController* MenuController = Cast<AMainMenuController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MenuController != nullptr)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		MenuController->ShowTutorialMenu();
	}
}

void UUI_MainMenuClass::OpenShop()
{
	AMainMenuController* MenuController = Cast<AMainMenuController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MenuController != nullptr)
	{
		MenuController->ShowSkinSelectionMenu();
	}
}

void UUI_MainMenuClass::ExitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	UE_LOG(LogTemp, Warning, TEXT("EXIT GAME"));
}
