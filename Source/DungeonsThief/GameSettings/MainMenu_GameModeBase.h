// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMainMenu_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class UMyGameInstance* MyGameInstance;
};
