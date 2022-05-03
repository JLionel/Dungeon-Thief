// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_ShopClass.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"

void UUI_ShopClass::NativeConstruct()
{
	Super::NativeConstruct();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance was found"));
		return;
	}

	BackToMenu->OnClicked.AddDynamic(this, &UUI_ShopClass::Back);

	GrantLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousGrantSkin);
	GrantRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextGrantSkin);
	GrantValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentGrantSkin);

	NomadLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousNomadSkin);
	NomadRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextNomadSkin);
	NomadValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentNomadSkin);

	EvaLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousEvaSkin);
	EvaRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextEvaSkin);
	EvaValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentEvaSkin);

	GetAvailableSkins(GrantSkins, GrantSkinsAvailable);
	GetAvailableSkins(NomadSkins, NomadSkinsAvailable);
	GetAvailableSkins(EvaSkins, EvaSkinsAvailable);

	GrantPreview->SetBrushFromTexture(GrantSkinsAvailable[0].CurrentSkinPreview);
	NomadPreview->SetBrushFromTexture(NomadSkinsAvailable[0].CurrentSkinPreview);
	EvaPreview->SetBrushFromTexture(EvaSkinsAvailable[0].CurrentSkinPreview);
}

void UUI_ShopClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

#pragma region Custom Skin Methods
void UUI_ShopClass::GetAvailableSkins(TArray<FCharacterSkin> Skins, TArray<FCharacterSkin>& AvailableSkins)
{
	for (auto Skin : Skins)
	{
		if (Skin.XPRequired <= MyGameInstance->GetPlayerXPLevel())
		{
			AvailableSkins.Add(Skin);
		}
	}
}

void UUI_ShopClass::ChooseNextSkin(int& CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview)
{
	CurrentIndex = (CurrentIndex + 1) % Skins.Num();

	Preview->SetBrushFromTexture(Skins[CurrentIndex].CurrentSkinPreview);
}

void UUI_ShopClass::ChoosePreviousSkin(int& CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview)
{
	CurrentIndex--;
	if (CurrentIndex < 0)
	{
		CurrentIndex = Skins.Num() - 1;
	}

	Preview->SetBrushFromTexture(Skins[CurrentIndex].CurrentSkinPreview);
}

USkeletalMesh* UUI_ShopClass::SelectSkin(int CurrentIndex, TArray<FCharacterSkin> Skins)
{
	FCharacterSkin SkinChosen = Skins[CurrentIndex];
	if (SkinChosen.CurrentMesh == nullptr && SkinChosen.CurrentSkinPreview == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Skeletal Mesh Or Image is null"));
		return nullptr;
	}

	return SkinChosen.CurrentMesh;
}
#pragma endregion

#pragma region GrantSkinSelection
void UUI_ShopClass::ChooseNextGrantSkin()
{
	ChooseNextSkin(CurrentGrantIndex, GrantSkinsAvailable, GrantPreview);
}

void UUI_ShopClass::ChoosePreviousGrantSkin()
{
	ChoosePreviousSkin(CurrentGrantIndex, GrantSkinsAvailable, GrantPreview);
}

void UUI_ShopClass::SelectCurrentGrantSkin()
{
	MyGameInstance->SetCurrentGrantSkin(SelectSkin(CurrentGrantIndex, GrantSkinsAvailable));
}
#pragma endregion

#pragma region NomadSkinSelection
void UUI_ShopClass::ChooseNextNomadSkin()
{
	ChooseNextSkin(CurrentNomadIndex, NomadSkinsAvailable, NomadPreview);
}

void UUI_ShopClass::ChoosePreviousNomadSkin()
{
	ChoosePreviousSkin(CurrentNomadIndex, NomadSkinsAvailable, NomadPreview);
}

void UUI_ShopClass::SelectCurrentNomadSkin()
{
	MyGameInstance->SetCurrentNomadSkin(SelectSkin(CurrentNomadIndex, NomadSkinsAvailable));
}
#pragma endregion

#pragma region EvaSkinSelection
void UUI_ShopClass::ChooseNextEvaSkin()
{
	ChooseNextSkin(CurrentEvaIndex, EvaSkinsAvailable, EvaPreview);
}

void UUI_ShopClass::ChoosePreviousEvaSkin()
{
	ChoosePreviousSkin(CurrentEvaIndex, EvaSkinsAvailable, EvaPreview);
}

void UUI_ShopClass::SelectCurrentEvaSkin()
{
	MyGameInstance->SetCurrentEvaSkin(SelectSkin(CurrentEvaIndex, EvaSkinsAvailable));
}
#pragma endregion
