// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsThief/Food/CarryingCharacter.h"
#include "DungeonsThief/Food/FoodSpot.h"

#include "MainCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AMainCharacter : public ACarryingCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();


protected:
	// For variable declaration
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* CAMERA SECTION */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float BaseLookupRate;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MaxZoom;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MinZoom;

	class AAnimationsHandler* AnimationHandler;

	UPROPERTY(EditAnywhere, Category = "WinAndLose")
	class UAnimMontage* WinMontage;

	UPROPERTY(EditAnywhere, Category = "WinAndLose")
	class UAnimMontage* LoseMontage;

	UPROPERTY(EditAnywhere, Category = "Animations")
	bool IsCrouch = false;

	UPROPERTY(VisibleAnywhere, Category = "PlayeModel")
	int CharacterID = 0;

	UPROPERTY(EditAnywhere, Category = "PlayeModel")
	TArray<USkeletalMesh*> PlayableCharacters;

	bool bCanMove;

	UPROPERTY(VisibleAnywhere, Category = "HUD")
	class AMainCharacterController* MainCharacterController;

	UPROPERTY(EditAnywhere, Category = "WinAndLose")
	float RagdollForceImpulse;

	class UMyGameInstance* MyGameInstance;

	/* Camera 3D preview */
	UPROPERTY(VisibleAnywhere, Category = "Preview Camera")
	class USpringArmComponent* PreviewCameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Preview Camera")
	class USceneCaptureComponent2D* PreviewCamera;

protected:
	//For function declaration

	/* Called for Spectating mode */
	void SpectatePlayer();

	/* Called for crouch player */
	void CrouchPlayer();

	/* Called for remove crouch state of player */
	void UnCrouchPlayer();

	/* Called for forward and backward movement */
	void MoveForward(float Value);

	/* Called for right and left movement */
	void MoveRight(float Value);

	/* Called via input to turn at a giver rate*/
	void TurnAtRate(float Rate);

	/* Called via input to look up and down at a given rate*/
	void LookupRate(float Rate);

	/* Called for scrolling in or out the camera view*/
	void ScrollInOut(float Value);

	/* Call pause function in player controller to show pause menu widget */
	UFUNCTION()
	void SetGamePause();

	/* For ragdoll behaviour */
	FVector GetXYRandomDirection(float XMin, float XMax, float YMin, float YMax);

	void SetPlayRagdoll();

public:
	FORCEINLINE void SetCanMove(bool value) { bCanMove = value; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void WinGame();

	UFUNCTION()
	void LoseGame();

	/* Called in UI to pick up a character for player */
	UFUNCTION()
	void DefinePlayerCharacter(int CharacterIndex);

	FORCEINLINE bool GetIsCrouching() { return IsCrouch; }

	FORCEINLINE int GetCharacterID() { return CharacterID; }

	void ChangeCharaterMesh(class USkeltalMesh* NewMesh);
};
