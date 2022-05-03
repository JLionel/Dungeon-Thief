// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodSpot.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CarryingCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API ACarryingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACarryingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float BaseSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float CrouchSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Food")
	bool IsCarryFood;

	UPROPERTY(VisibleAnywhere, Category = "Other")
	class AActor* NearFoodActor;

	UPROPERTY(VisibleAnywhere, Category = "Food")
	AActor* FoodCarriedActor;

	UPROPERTY(VisibleAnywhere, Category = "FoodSpot")
	bool NearToFoodSpot;

	UPROPERTY(VisibleAnywhere, Category = "FoodSpot")
	AFoodSpot* SpotReference;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float SpeedBonus = 1;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CarrySpeedBonus = 1;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CrouchSpeedBonus = 1;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CarryItem();
	void PutItemOnSpot();
	void SetPlayerSpeed();

	UFUNCTION()
	void InteractWithItem();

	FORCEINLINE void SetNearFoodActor(AActor* NewActor) { NearFoodActor = NewActor; }
	FORCEINLINE void SetSpeed(float NewSpeed) { GetCharacterMovement()->MaxWalkSpeed = NewSpeed; };

	FORCEINLINE void SetIsNearSpot(bool NewState) { NearToFoodSpot = NewState; };
	void SetSpotReference(AFoodSpot* Reference);

	FORCEINLINE bool GetIsCarryFood() { return IsCarryFood; }
	FORCEINLINE AActor* GetFoodCarried() { return FoodCarriedActor; }
	FORCEINLINE AActor* GetPlayerNearFoodActor() { return NearFoodActor; }
	FORCEINLINE FVector GetItemSocket() { return GetMesh()->GetSocketLocation("ItemSocket"); };
	FORCEINLINE FVector GetFloorSocket() { return GetMesh()->GetSocketLocation("FloorSocket"); };

	UFUNCTION()
	void DropItem();
};
