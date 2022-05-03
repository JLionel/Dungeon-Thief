// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHidingPlace.h"

#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

class AMyGameMode;
// Sets default values
APlayerHidingPlace::APlayerHidingPlace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerHidingPlace::OnBoxOverlapBegin);
}

// Called when the game starts or when spawned
void APlayerHidingPlace::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeBase is null"));
		return;
	}

	MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}

	FoodManager = MyGameMode->GetFoodManager();
}

// Called every frame
void APlayerHidingPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerHidingPlace::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	AFood* FoodEnter = Cast<AFood>(OtherActor);
	if (FoodEnter == nullptr)
	{
		//OtherActor isn't a food alone
		return;
	}

	MyGameMode->GainPoints(FoodEnter->GetFoodPoints());
	UGameplayStatics::PlaySoundAtLocation(this, WinPointsSound, GetActorLocation());

	if (FoodManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FoodManager is null"));
		return;
	}

	FoodManager->RemoveFoodFromWorldList(FoodEnter);

	AMainCharacter* Player = Cast<AMainCharacter>(FoodEnter->GetCharacterCarryingMe());
	if (Player != nullptr)
	{
		Player->DropItem();
		Player->SetNearFoodActor(nullptr);
	}

	FoodEnter->Destroy();
}
