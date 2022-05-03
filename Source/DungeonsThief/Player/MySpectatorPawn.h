// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
public:
	AMySpectatorPawn();

protected:
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UnSpectatePlayer();

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	class UMyGameInstance* MyGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	AController* SpectatorPawnController;
};
