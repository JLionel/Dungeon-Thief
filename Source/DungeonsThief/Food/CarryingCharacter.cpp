// Fill out your copyright notice in the Description page of Project Settings.


#include "CarryingCharacter.h"
#include "FoodSpot.h"
#include "Food.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACarryingCharacter::ACarryingCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarryingCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACarryingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FoodCarriedActor == nullptr)
	{
		return;
	}

	FoodCarriedActor->SetActorLocation(this->GetItemSocket());
}

/**
* @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
*/
void ACarryingCharacter::InteractWithItem()
{
	if (NearFoodActor != nullptr)
	{
		AFood* NearFood = Cast<AFood>(NearFoodActor);
		if (NearFood == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Near Food is null"));
			return;
		}

		if (IsCarryFood == false)
		{
			CarryItem();
			NearFood->BeTake();
		}
		else
		{
			DropItem();
		}
	}
	else
	{
		if (NearToFoodSpot == true)
		{
			if (IsCarryFood == true)
			{
				PutItemOnSpot();
			}
		}
		else
		{
			DropItem();
		}
	}
}


/**
* @brief Put item (food) on a nearest spot
*/
void ACarryingCharacter::PutItemOnSpot()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	if (FoodCarriedActor == nullptr && NearFoodActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Food carry actor or NearFoodActor is null"));
		return;
	}

	FoodCarriedActor->SetActorLocation(SpotReference->GetSpawnPoint()->GetComponentLocation());
	NearFoodActor = FoodCarriedActor;

	AFood* ModifyFoodData = Cast<AFood>(NearFoodActor);
	if (ModifyFoodData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ModifyFoodDate is null"));
		return;
	}

	ModifyFoodData->SetIsOnSpot(true);

	FoodCarriedActor = nullptr;
	IsCarryFood = false;
}

/**
* @brief Set player speed in depend of it's worn item
*/
void ACarryingCharacter::SetPlayerSpeed()
{
	if (IsCarryFood)
	{
		AFood* FoodCarried = Cast<AFood>(FoodCarriedActor);

		GetCharacterMovement()->MaxWalkSpeed = (BaseSpeed * 0.5) * CarrySpeedBonus;
		if (FoodCarried == nullptr)
		{
			return;
		}

		// if player actually carry food
		GetCharacterMovement()->MaxWalkSpeed = (BaseSpeed * FoodCarried->GetSpeedReduction()) * CarrySpeedBonus;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * SpeedBonus;
	}
}

void ACarryingCharacter::SetSpotReference(AFoodSpot* Reference)
{
	if (Reference != nullptr)
	{
		SpotReference = Reference;
	}
	else
	{
		SpotReference = nullptr;
	}
}

/**
* @brief Event when player carry item
*/
void ACarryingCharacter::CarryItem()
{
	if (IsCarryFood == false)
	{
		IsCarryFood = true;

		if (NearFoodActor == nullptr)
		{
			return;
		}

		FoodCarriedActor = NearFoodActor;

		AFood* ModifyFoodData = Cast<AFood>(FoodCarriedActor);
		if (ModifyFoodData == nullptr)
		{
			return;
		}

		ModifyFoodData->SetIsOnSpot(false);
		ModifyFoodData->SetCharacterCarryingMe(this);

		NearFoodActor = nullptr;

		SetPlayerSpeed();

		if (FoodCarriedActor == nullptr)
		{
			return;
		}

		FoodCarriedActor->SetActorLocation(this->GetActorLocation());
		FoodCarriedActor->SetActorRotation(GetActorRotation());
	}
}

/**
* @brief Event when player drop item (on floor or on spot)
*/
void ACarryingCharacter::DropItem()
{
	if (IsCarryFood == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		IsCarryFood = false;

		if (FoodCarriedActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("FoddCarriedActor is null"));
			return;
		}

		NearFoodActor = FoodCarriedActor;

		AFood* ModifyFood = Cast<AFood>(NearFoodActor);
		if (ModifyFood == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ModifyFood is null"));
			return;
		}

		ModifyFood->SetCharacterCarryingMe(nullptr);

		FVector ForwardVec = GetActorForwardVector();
		ForwardVec.Normalize();
		FoodCarriedActor->SetActorLocation(GetActorLocation() + ForwardVec * 60);
		ModifyFood->BeDrop();

		FoodCarriedActor = nullptr;
		IsCarryFood = false;
	}
}
