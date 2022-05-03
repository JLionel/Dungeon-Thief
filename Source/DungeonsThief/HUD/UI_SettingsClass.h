// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerInput.h"
#include "UI_SettingsClass.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_SettingsClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Back();

	UFUNCTION()
	FInputActionKeyMapping GetActionMapping(FString KeyName) const;

	UFUNCTION()
	FInputAxisKeyMapping GetAxisMapping(FString KeyName, bool bPositiveScale) const;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* MoveForwardInput;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* MoveBackwardInput;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* MoveRightInput;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* MoveLeftInput;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* InteractionInput;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UInputKeySelector* CrouchInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnBack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnResetSave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UTextBlock* TxtInputInfo;

	UPROPERTY(VisibleAnywhere)
	UInputSettings* InputSettings;

	UPROPERTY(EditAnywhere)
	TArray<FString> MappingName;

	class UMyGameInstance* MyGameInstance;


protected:
	UFUNCTION()
	void OnInteractKeySelected(FInputChord InputChord);

	UFUNCTION()
	void OnCrouchKeySelected(FInputChord InputChord);

	UFUNCTION()
	void OnForwardKeySelected(FInputChord InputChord);

	UFUNCTION()
	void OnBackwardKeySelected(FInputChord InputChord);

	UFUNCTION()
	void OnRightKeySelected(FInputChord InputChord);

	UFUNCTION()
	void OnLeftKeySelected(FInputChord InputChord);

	UFUNCTION()
	bool IsAvailableKey(FKey Key) const;

	UFUNCTION()
	void ErrorKey(FString NameMapping, bool bPositiveScale) const;

	UFUNCTION()
	void ResetSave();

	float PositiveScale = 1;
	float NegativeScale = -1;
};
