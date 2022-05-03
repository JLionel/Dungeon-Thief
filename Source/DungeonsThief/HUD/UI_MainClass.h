// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MainClass.generated.h"


/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_MainClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* FoodBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScorePoint;

	class AMyGameMode* MyGameMode;
	class AMyGameState* MyGameState;
	class UMyGameInstance* MyGameInstance;

	UFUNCTION()
	void UpdateProgression();
};
