// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_PauseClass.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_PauseClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnResume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnMenu;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void ReturnToMenu();

	UPROPERTY(EditAnywhere, Category = "UI infos")
	FName MainMenuLevelName = FName("MainMenuLevel");

	UPROPERTY(EditAnywhere, Category = "UI infos")
	class AMyGameMode* MyGameMode;
};
