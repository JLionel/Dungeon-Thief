// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerHidingPlace.generated.h"

UCLASS()
class DUNGEONSTHIEF_API APlayerHidingPlace : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerHidingPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int FoodCount;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* WinPointsSound;

	UPROPERTY(EditAnywhere)
	class AFoodManager* FoodManager;

	class AMyGameMode* MyGameMode;

	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
