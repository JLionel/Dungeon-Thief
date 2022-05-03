// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodManager.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "Kismet/GameplayStatics.h"

class AMyGameMode;
// Sets default values
AFoodManager::AFoodManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFoodManager::BeginPlay()
{
	Super::BeginPlay();

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

	MyGameMode->InitFoodManager(this);

	int FirstSpotWithFood = FMath::FRandRange(0, SpotsArray.Num() - 1);

	AFoodSpot* FoodSpot = SpotsArray[FirstSpotWithFood];
	if (FoodSpot)
	{
		AFood* SpawnedFood = SpawnFood(FoodSpot->GetSpawnPoint()->GetComponentLocation());
		SpawnedFood->SetIsOnSpot(true);
	}
}

// Called every frame
void AFoodManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFoodManager::RemoveFoodFromWorldList(AFood* FoodToRemove)
{
	if (AllFoodInWorld.Contains(FoodToRemove))
	{
		AllFoodInWorld.Remove(FoodToRemove);
	}
}

AFood* AFoodManager::SpawnFood(FVector SpawnLocation)
{
	AFood* SpawnedFood = GetWorld()->SpawnActor<AFood>(FoodActor, SpawnLocation, GetActorRotation());
	AllFoodInWorld.Add(SpawnedFood);
	return SpawnedFood;
}
