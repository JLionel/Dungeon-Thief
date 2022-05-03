// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Player/MySpectatorPawn.h"

#include "DungeonsThief/GameSettings/MyGameInstance.h"

AMySpectatorPawn::AMySpectatorPawn()
{
}

void AMySpectatorPawn::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}


void AMySpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AMySpectatorPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMySpectatorPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUpSpectator", this, &AMySpectatorPawn::MoveUp_World);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMySpectatorPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMySpectatorPawn::LookUpAtRate);


	PlayerInputComponent->BindAction("Spectate", IE_Pressed, this, &AMySpectatorPawn::UnSpectatePlayer);
}

void AMySpectatorPawn::UnSpectatePlayer()
{
	SpectatorPawnController = GetController();
	if (SpectatorPawnController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No controller found in Spectate"))
		return;
	}

	SpectatorPawnController->ChangeState(NAME_Playing);
	SpectatorPawnController->Possess(MyGameInstance->GetMainPlayerPawn());
}
