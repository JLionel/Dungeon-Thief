#include "DungeonsThief/HUD/UI_TutorialClass.h"

#include "MainMenuController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_TutorialClass::NativeConstruct()
{
	Super::NativeConstruct();

	BtnBack->OnClicked.AddUniqueDynamic(this, &UUI_TutorialClass::Back);
}

void UUI_TutorialClass::Back()
{
	AMainMenuController* MenuController = Cast<AMainMenuController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MenuController != nullptr)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		MenuController->ShowMainMenu();
	}
}
