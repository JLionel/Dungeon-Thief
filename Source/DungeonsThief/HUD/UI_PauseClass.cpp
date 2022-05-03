// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_PauseClass.h"

#include "Components/Button.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"
#include "Kismet/GameplayStatics.h"


void UUI_PauseClass::NativeConstruct()
{
	Super::NativeConstruct();


	BtnResume->OnClicked.AddUniqueDynamic(this, &UUI_PauseClass::ResumeGame);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUI_PauseClass::ReturnToMenu);
}

void UUI_PauseClass::ResumeGame()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::SetGamePaused(World, false);
		this->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(World, 0)->bShowMouseCursor = false;
	}
}

void UUI_PauseClass::ReturnToMenu()
{
	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("START GAME"));

	if (World)
	{
		MyGameMode = Cast<AMyGameMode>(World->GetAuthGameMode());
		if (MyGameMode)
		{
			MyGameMode->GetSpawnManager()->StopAllTimeHandle();
		}
		//UGameplayStatics::SetGamePaused(World, false);
		UGameplayStatics::OpenLevel(World, MainMenuLevelName);
	}
}
