// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "MainCharacterController.h"
#include "DungeonsThief/Managers/AAnimationsHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


class AMyGameMode;
// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Boom Creation
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true; //Rotation base on the character controller

	//Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the camera boom  
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.0f;
	BaseLookupRate = 65.0f;

	//Don't rotate when the controller rotate (let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//Character Movement configuration
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = .2f;

	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CrouchSpeed = BaseSpeed / 2;

	MaxZoom = 600.0f;
	MinZoom = 200.0f;

	AnimationHandler = CreateDefaultSubobject<AAnimationsHandler>(TEXT("AnimationHandler"));

	PreviewCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("PreviewCameraBoom"));
	PreviewCameraBoom->SetupAttachment(GetRootComponent());
	PreviewCameraBoom->TargetArmLength = 50.0f;
	PreviewCameraBoom->bUsePawnControlRotation = false;

	PreviewCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Preview Camera"));
	PreviewCamera->SetupAttachment(PreviewCameraBoom, USpringArmComponent::SocketName);
	PreviewCamera->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	bCanMove = true;

	RagdollForceImpulse = 10;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainCharacterController = Cast<AMainCharacterController>(GetController());

	//set where the camera is looking at
	CameraBoom->SetRelativeLocation(FVector(0, 0, 60));

	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * SpeedBonus;

	//Bind method with the GameMode
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}

	MyGameMode->OnGameWin.AddDynamic(this, &AMainCharacter::WinGame);
	MyGameMode->OnGameLose.AddDynamic(this, &AMainCharacter::LoseGame);

	PreviewCamera->ShowOnlyActors.Add(this);
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
 * Setup player inputs with custom functions
 */
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookupRate);

	PlayerInputComponent->BindAxis("ScrollCamera", this, &AMainCharacter::ScrollInOut);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::InteractWithItem);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::CrouchPlayer);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::UnCrouchPlayer);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMainCharacter::SetGamePause);

	PlayerInputComponent->BindAction("Spectate", IE_Pressed, this, &AMainCharacter::SpectatePlayer);
}


//////////////////// PLAYER MOVEMENT ////////////////////
#pragma region Player movement

/*
 * Move the character in the forward or backward direction
 */
void AMainCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::CrouchPlayer()
{
	if (IsCrouch == false && IsCarryFood == false)
	{
		Crouch();
		PreviewCameraBoom->TargetArmLength = -120.0f;
		GetCharacterMovement()->MaxWalkSpeed = (BaseSpeed / 1.75) * CrouchSpeedBonus;
		IsCrouch = true;
		GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
}


void AMainCharacter::UnCrouchPlayer()
{
	if (IsCrouch == true)
	{
		UnCrouch();
		PreviewCameraBoom->TargetArmLength = -60.0f;
		SetPlayerSpeed();
		IsCrouch = false;
	}
}


/*
 * Move the character in the right or left direction
 */
void AMainCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion


//////////////////// CAMERA SYSTEM ////////////////////
#pragma region Camera System

void AMainCharacter::TurnAtRate(float Rate)
{
	if (bCanMove)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMainCharacter::LookupRate(float Rate)
{
	if (bCanMove)
	{
		AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMainCharacter::ScrollInOut(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		float CurrentArmLenght = CameraBoom->TargetArmLength + Value;

		if (CurrentArmLenght < MaxZoom && CurrentArmLenght > MinZoom)
		{
			CameraBoom->TargetArmLength += Value;
		}
	}
}


#pragma endregion


//////////////////// WIN / LOSE BEHAVIOUR ////////////////////
#pragma region Win/Lose Behvaiour

void AMainCharacter::WinGame()
{
	if (AnimationHandler && WinMontage)
	{
		AnimationHandler->PlayAnimation(this, WinMontage);
		bCanMove = false;
	}

	if (MainCharacterController)
	{
		MainCharacterController->ShowWinScreen(true);
		MainCharacterController->ShowMainMenu(false);
	}
}

void AMainCharacter::LoseGame()
{
	SetPlayRagdoll();

	if (MainCharacterController)
	{
		MainCharacterController->ShowLoseScreen(true);
		MainCharacterController->ShowMainMenu(false);
	}
}


#pragma endregion

/**
 * @brief Define a character and his specification for the player
 * @param CharacterIndex Index for character in character array
 */
void AMainCharacter::DefinePlayerCharacter(int CharacterIndex)
{
	CharacterID = CharacterIndex;

	USkeletalMesh* ChooseMesh = PlayableCharacters[CharacterIndex];

	switch (CharacterIndex)
	{
	case 0:
		CarrySpeedBonus = 1.1;
		ChooseMesh = MyGameInstance->GetHasCustomGrantSkin()
			             ? MyGameInstance->GetCurrentGrantSkin()
			             : PlayableCharacters[CharacterIndex];
		break;

	case 1:
		SpeedBonus = 1.1;
		ChooseMesh = MyGameInstance->GetHasCustomNomadSkin()
			             ? MyGameInstance->GetCurrentNomadSkin()
			             : PlayableCharacters[CharacterIndex];
		break;

	case 2:
		CrouchSpeedBonus = 1.05;
		ChooseMesh = MyGameInstance->GetHasCustomEvaSkin()
			             ? MyGameInstance->GetCurrentEvaSkin()
			             : PlayableCharacters[CharacterIndex];
		break;

	default:
		break;
	}

	GetMesh()->SetSkeletalMesh(ChooseMesh);
}

void AMainCharacter::ChangeCharaterMesh(USkeltalMesh* NewMesh)
{
	if (MyGameInstance == nullptr)
	{
		return;
	}

	GetMesh()->SetSkeletalMeshWithoutResettingAnimation(MyGameInstance->GetCurrentGrantSkin());
}


void AMainCharacter::SpectatePlayer()
{
	MainCharacterController->ChangeState(NAME_Spectating);
}

void AMainCharacter::SetGamePause()
{
	APlayerController* ControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainCharacterController* Player = Cast<AMainCharacterController>(ControllerRef);

	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Main Character : Player is null"));
		return;
	}

	Player->ShowPauseMenu(true);
}

FVector AMainCharacter::GetXYRandomDirection(float XMin, float XMax, float YMin, float YMax)
{
	float X = FMath::RandRange(XMin, XMax);
	float Y = FMath::RandRange(YMin, YMax);

	return FVector(X, Y, 5);
}

void AMainCharacter::SetPlayRagdoll()
{
	bCanMove = false;

	DropItem();

	USkeletalMeshComponent* PlayerMesh = GetMesh();
	if (PlayerMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No skeletal mesh was found on the player"));
		return;
	}

	PlayerMesh->SetAllBodiesBelowSimulatePhysics(FName("Pelvis"), true, true);
	PlayerMesh->SetAllBodiesBelowPhysicsBlendWeight(FName("Pelvis"), 2.0, false, true);

	PlayerMesh->SetSimulatePhysics(true);
	PlayerMesh->AddImpulse(GetXYRandomDirection(-5, 5, -5, 5) * RagdollForceImpulse, FName("Pelvis"), true);
}
