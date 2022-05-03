// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_SettingsClass.h"

#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

void UUI_SettingsClass::NativeConstruct()
{
	Super::NativeConstruct();

	InputSettings = UInputSettings::GetInputSettings();

	//Assign each selector to a keybind
	InteractionInput->SetSelectedKey(GetActionMapping(MappingName[0]).Key);
	CrouchInput->SetSelectedKey(GetActionMapping(MappingName[1]).Key);
	MoveForwardInput->SetSelectedKey(GetAxisMapping(MappingName[2], true).Key);
	MoveBackwardInput->SetSelectedKey(GetAxisMapping(MappingName[2], false).Key);
	MoveRightInput->SetSelectedKey(GetAxisMapping(MappingName[3], true).Key);
	MoveLeftInput->SetSelectedKey(GetAxisMapping(MappingName[3], false).Key);

	//Add event to each buttons
	InteractionInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnInteractKeySelected);
	CrouchInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnCrouchKeySelected);
	MoveForwardInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnForwardKeySelected);
	MoveBackwardInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnBackwardKeySelected);
	MoveRightInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnRightKeySelected);
	MoveLeftInput->OnKeySelected.AddDynamic(this, &UUI_SettingsClass::OnLeftKeySelected);

	BtnBack->OnClicked.AddDynamic(this, &UUI_SettingsClass::Back);
	BtnResetSave->OnClicked.AddDynamic(this, &UUI_SettingsClass::ResetSave);

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}


////////////// INPUT SETTINGS SYSTEM //////////////
#pragma region Input settings

FInputActionKeyMapping UUI_SettingsClass::GetActionMapping(FString KeyName) const
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(static_cast<FName>(KeyName), OutMappings);

	return OutMappings[0];
}

FInputAxisKeyMapping UUI_SettingsClass::GetAxisMapping(FString KeyName, const bool bPositiveScale) const
{
	TArray<FInputAxisKeyMapping> OutMappings;
	InputSettings->GetAxisMappingByName(static_cast<FName>(KeyName), OutMappings);

	FInputAxisKeyMapping KeyMapping;

	for (const auto Mapping : OutMappings)
	{
		if (bPositiveScale)
		{
			if (Mapping.Scale > 0)
			{
				KeyMapping = Mapping;
			}
		}
		else
		{
			KeyMapping = Mapping;
		}
	}

	return KeyMapping;
}

/**
 * @brief Event when the Interaction Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnInteractKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[0], true);
		return;
	}

	InputSettings->RemoveActionMapping(GetActionMapping(MappingName[0]));
	InputSettings->AddActionMapping(FInputActionKeyMapping(static_cast<FName>(MappingName[0]), InputChord.Key));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event when the Crouch Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnCrouchKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[1], true);
		return;
	}

	InputSettings->RemoveActionMapping(GetActionMapping(MappingName[1]));
	InputSettings->AddActionMapping(FInputActionKeyMapping(static_cast<FName>(MappingName[1]), InputChord.Key));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event when the Forward Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnForwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], true);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], true));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key,
	                                                   PositiveScale));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event when the Backward Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnBackwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], false);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], false));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key,
	                                                   NegativeScale));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event when the Right Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnRightKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[3], true);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[3], true));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[3]), InputChord.Key,
	                                                   PositiveScale));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event when the Left Key button is selected (to change this keybind)
 */
void UUI_SettingsClass::OnLeftKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[3], false);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[3], false));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[3]), InputChord.Key,
	                                                   NegativeScale));
	TxtInputInfo->SetVisibility(ESlateVisibility::Hidden);
}


bool UUI_SettingsClass::IsAvailableKey(const FKey Key) const
{
	for (auto ActionKeyMapping : InputSettings->GetActionMappings())
	{
		if (ActionKeyMapping.Key == Key)
		{
			return true;
		}
	}

	for (auto AxisKeyMapping : InputSettings->GetAxisMappings())
	{
		if (AxisKeyMapping.Key == Key)
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Event when the player use à key already used
 */
void UUI_SettingsClass::ErrorKey(const FString NameMapping, const bool bPositiveScale) const
{
	TxtInputInfo->SetVisibility(ESlateVisibility::Visible);

	if (NameMapping == MappingName[0])
	{
		InteractionInput->SetSelectedKey(GetActionMapping(NameMapping).Key);
	}
	else if (NameMapping == MappingName[1])
	{
		CrouchInput->SetSelectedKey(GetActionMapping(NameMapping).Key);
	}
	else if (NameMapping == MappingName[2])
	{
		if (bPositiveScale)
		{
			MoveForwardInput->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		}
		else
		{
			MoveBackwardInput->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		}
	}
	else if (NameMapping == MappingName[3])
	{
		if (bPositiveScale)
		{
			MoveRightInput->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		}
		else
		{
			MoveLeftInput->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		}
	}
}

#pragma endregion


/**
 * @brief Event for the Back button
 */
void UUI_SettingsClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Event for reset the game save
 */
void UUI_SettingsClass::ResetSave()
{
	MyGameInstance->ResetSave();
}
