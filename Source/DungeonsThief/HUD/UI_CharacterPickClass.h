// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_CharacterPickClass.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_CharacterPickClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnCharacter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnCharacter2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnCharacter3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UTextBlock* CharacterInfoText;


	UFUNCTION()
	void ChooseCharacter1();

	UFUNCTION()
	void ChooseCharacter2();

	UFUNCTION()
	void ChooseCharacter3();

	UFUNCTION()
	void HoverCharacterButton1();

	UFUNCTION()
	void HoverCharacterButton2();

	UFUNCTION()
	void HoverCharacterButton3();

	UFUNCTION()
	void HideHUD();

	UFUNCTION()
	void UpdateCharacterInfoText(FString InfoText);
};
