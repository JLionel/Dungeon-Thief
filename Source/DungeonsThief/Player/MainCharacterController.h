// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacterController();

protected:
	virtual void BeginPlay() override;

	/** Reference to the UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> WMain;

	/** Variable to hold the wodget after creating it */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UUserWidget* MainWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WWinScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* WinScreenWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WLoseScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* LoseScreenWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WPauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* PauseMenuWidget;

	/** Reference to the character pick UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> WCharacterPick;

	/** Variable to hold the Character pick widget after creating it */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UUserWidget* CharacterPickWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller infos")
	bool CanPause = false;

	class AMyGameState* MyGameState;
	class UMyGameInstance* MyGameInstance;

public :
	UFUNCTION()
	void ShowWinScreen(bool Visibility);
	
	UFUNCTION()
	void ShowLoseScreen(bool Visibility);

	UFUNCTION()
	void ShowPauseMenu(bool Visibility);

	UFUNCTION()
	void ShowMainMenu(bool Visibility);

	void SetCanPause(bool state);
};
