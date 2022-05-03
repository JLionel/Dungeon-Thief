// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameState.h"
#include "DungeonsThief/HUD/UI_ShopClass.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameplayMode GameplayMode = EGameplayMode::EGM_NormalMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BestScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PlayerXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PlayerXPLevel = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* MainPlayerPawn;

#pragma region Custom Skins
	UPROPERTY(VisibleAnywhere, Category = "Custom Skin | Grant")
	class USkeletalMesh* CurrentGrantSkin;
	bool bHasCustomGrantSkin;

	UPROPERTY(VisibleAnywhere, Category = "Custom Skin | Nomad")
	class USkeletalMesh* CurrentNomadSkin;
	bool bHasCustomNomadSkin;

	UPROPERTY(VisibleAnywhere, Category = "Custom Skin | Eva")
	class USkeletalMesh* CurrentEvaSkin;
	bool bHasCustomEvaSkin;
#pragma endregion

public:
	FORCEINLINE void SetGameplayMode(EGameplayMode GameplayModeValue) { GameplayMode = GameplayModeValue; }
	FORCEINLINE EGameplayMode GetGameplayMode() { return GameplayMode; }

	FORCEINLINE void SetMainPlayerPawn(APawn* PawnValue) { MainPlayerPawn = PawnValue; }
	FORCEINLINE APawn* GetMainPlayerPawn() { return MainPlayerPawn; }

	//Best score system variable
	FORCEINLINE int GetBestScore() { return BestScore; }
	FORCEINLINE void SetBestScore(int NewBestScore);

	//Player XP system variable
	FORCEINLINE int GetPlayerXP() { return PlayerXP; }
	FORCEINLINE void AddPlayerXP(int AmountOfXP);

	//Plauer XP Level system variable
	FORCEINLINE int GetPlayerXPLevel() { return PlayerXPLevel; }

	//Custom Skin
#pragma region GrantSkin
	FORCEINLINE class USkeletalMesh* GetCurrentGrantSkin() { return CurrentGrantSkin; }
	FORCEINLINE void SetCurrentGrantSkin(class USkeletalMesh* NewMesh)
	{
		CurrentGrantSkin = NewMesh;
		bHasCustomGrantSkin = true;
	}

	FORCEINLINE bool GetHasCustomGrantSkin() { return bHasCustomGrantSkin; }
#pragma endregion

#pragma region NomadSkin
	FORCEINLINE class USkeletalMesh* GetCurrentNomadSkin() { return CurrentNomadSkin; }
	FORCEINLINE void SetCurrentNomadSkin(class USkeletalMesh* NewMesh)
	{
		CurrentNomadSkin = NewMesh;
		bHasCustomNomadSkin = true;
	}

	FORCEINLINE bool GetHasCustomNomadSkin() { return bHasCustomNomadSkin; }
#pragma endregion

#pragma region EvaSkin
	FORCEINLINE class USkeletalMesh* GetCurrentEvaSkin() { return CurrentEvaSkin; }
	FORCEINLINE void SetCurrentEvaSkin(class USkeletalMesh* NewMesh)
	{
		CurrentEvaSkin = NewMesh;
		bHasCustomEvaSkin = true;
	}

	FORCEINLINE bool GetHasCustomEvaSkin() { return bHasCustomEvaSkin; }
#pragma endregion

	//Save system
	void SaveGame();
	void LoadGame();

	void ResetSave();
};
