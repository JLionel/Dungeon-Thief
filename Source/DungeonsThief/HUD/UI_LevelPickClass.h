// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_LevelPickClass.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_LevelPickClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnDungeonLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnForgeLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnBack;

	UPROPERTY(EditAnywhere, Category = "UI infos")
	FName DungeonLevelName = FName("MainLevel");

	UPROPERTY(EditAnywhere, Category = "UI infos")
	FName ForgeLevelName = FName("ForgeLevel");

	UFUNCTION()
	void PlayDungeonLevel();

	UFUNCTION()
	void PlayForgeLevel();

	UFUNCTION()
	void Back();
};
