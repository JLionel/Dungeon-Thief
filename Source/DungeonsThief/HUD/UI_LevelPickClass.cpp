#include "DungeonsThief/HUD/UI_LevelPickClass.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_LevelPickClass::NativeConstruct()
{
	Super::NativeConstruct();

	BtnDungeonLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::PlayDungeonLevel);
	BtnForgeLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::PlayForgeLevel);
	BtnBack->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::Back);
}

void UUI_LevelPickClass::PlayDungeonLevel()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, DungeonLevelName);
	}
}

void UUI_LevelPickClass::PlayForgeLevel()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, ForgeLevelName);
	}
}

void UUI_LevelPickClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
