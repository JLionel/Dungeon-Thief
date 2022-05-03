// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_CharacterPickClass.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Player/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"

void UUI_CharacterPickClass::NativeConstruct()
{
	Super::NativeConstruct();

	BtnCharacter1->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter1);
	BtnCharacter2->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter2);
	BtnCharacter3->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter3);

	BtnCharacter1->OnHovered.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverCharacterButton1);
	BtnCharacter2->OnHovered.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverCharacterButton2);
	BtnCharacter3->OnHovered.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverCharacterButton3);
}

//////////////// BUTTONS CLICK EVENTS ////////////////
#pragma region Buttons click events

void UUI_CharacterPickClass::ChooseCharacter1()
{
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(0);
		HideHUD();
	}
}

void UUI_CharacterPickClass::ChooseCharacter2()
{
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(1);
		HideHUD();
	}
}

void UUI_CharacterPickClass::ChooseCharacter3()
{
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(2);
		HideHUD();
	}
}

#pragma endregion

//////////////// HOVER BUTTON EVENTS ////////////////
#pragma region Hover button events

void UUI_CharacterPickClass::HoverCharacterButton1()
{
	UpdateCharacterInfoText("Walk speed bonus when carry item");
}

void UUI_CharacterPickClass::HoverCharacterButton2()
{
	UpdateCharacterInfoText("Walk speed bonus ( without item )");
}

void UUI_CharacterPickClass::HoverCharacterButton3()
{
	UpdateCharacterInfoText("Crouch speed bonus");
}

#pragma endregion

void UUI_CharacterPickClass::HideHUD()
{
	AMainCharacterController* ControllerRef = Cast<AMainCharacterController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (ControllerRef != nullptr)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		ControllerRef->SetCanPause(true);
	}
}


/**
 * @brief Change the text of the Character Info text block
 * @param InfoText Text to set in the text block
 */
void UUI_CharacterPickClass::UpdateCharacterInfoText(FString InfoText)
{
	FText Text = FText::FromString(InfoText);
	CharacterInfoText->SetText(Text);
}
