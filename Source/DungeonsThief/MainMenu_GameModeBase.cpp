// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/GameSettings/MainMenu_GameModeBase.h"

#include "LevelSequencePlayer.h"
#include "GameSettings/MyGameInstance.h"
#include "HUD/MainMenuController.h"
#include "Kismet/GameplayStatics.h"

void AMainMenu_GameModeBase::BeginPlay()
{
    MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance == nullptr)
	{
		return;
	}
	
	MyGameInstance->LoadGame();
}
