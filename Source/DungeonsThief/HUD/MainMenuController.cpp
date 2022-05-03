// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/MainMenuController.h"

#include "Blueprint/UserWidget.h"
#include "DungeonsThief/Player/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidget)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidget);
		MainMenu->AddToViewport();
		MainMenu->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}

	if (PickLevelWidget)
	{
		PickLevelMenu = CreateWidget<UUserWidget>(this, PickLevelWidget);
		PickLevelMenu->AddToViewport();
		PickLevelMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = true;
	}

	if (SettingsWidget)
	{
		SettingsMenu = CreateWidget<UUserWidget>(this, SettingsWidget);
		SettingsMenu->AddToViewport();
		SettingsMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = true;
	}

	if (TutorialWidget)
	{
		TutorialMenu = CreateWidget<UUserWidget>(this, TutorialWidget);
		TutorialMenu->AddToViewport();
		TutorialMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = true;
	}

	if (SkinSelectionWidget)
	{
		SkinSelectionMenu = CreateWidget<UUserWidget>(this, SkinSelectionWidget);
		SkinSelectionMenu->AddToViewport();
		SkinSelectionMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = true;
	}
}

void AMainMenuController::ShowSkinSelectionMenu()
{
	SkinSelectionMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuController::ShowPickLevelMenu()
{
	PickLevelMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuController::ShowSettingsMenu()
{
	SettingsMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuController::ShowTutorialMenu()
{
	TutorialMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuController::ShowMainMenu()
{
	MainMenu->SetVisibility(ESlateVisibility::Visible);
}
