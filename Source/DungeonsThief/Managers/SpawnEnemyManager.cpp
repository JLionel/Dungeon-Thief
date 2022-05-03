// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Managers/SpawnEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"

class AMyGameMode;
// Sets default values
ASpawnEnemyManager::ASpawnEnemyManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeleteEnemyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DeleteEnemyBoxComponent"));
	DeleteEnemyBoxComponent->SetupAttachment(GetRootComponent());
	DeleteEnemyBoxComponent->InitBoxExtent(FVector(100, 10, 100));

	SpawnLocation = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(DeleteEnemyBoxComponent);
	SpawnLocation->InitSphereRadius(10);

	MinSpawnDelay = 0.0f;
	MaxSpawnDelay = 5.99f;

	FirstSpawnDelay = 60;

	bIsFirstSpawn = true;
	bGlobalWaitAI = false;
}

// Called when the game starts or when spawned
void ASpawnEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	DeleteEnemyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASpawnEnemyManager::DeleteBoxOnOverlapEnd);

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Getting GameMode failed"));
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameMode is null"));
		return;
	}

	MyGameMode->OnGameWin.AddDynamic(this, &ASpawnEnemyManager::StopAllTimeHandle);
	MyGameMode->OnGameLose.AddDynamic(this, &ASpawnEnemyManager::StopAllTimeHandle);

	CurrentEnemyToSpawn = GetWorld()->GetName() == "MainLevel" ? FirstEnemyToSpawn : SecondEnemyToSpawn;

	//First spawn : 2 enemies are instanciated + wait 60s to instanciate a third one
	SpawnEnemy(60);
}

// Called every frame
void ASpawnEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnEnemyManager::SetupEnemy(AAIEnemyCharacter* EnemyCharacter)
{
	if (EnemyCharacter)
	{
		AAIEnemyController* AIController = Cast<AAIEnemyController>(EnemyCharacter->GetController());

		if (AIController)
		{
			AIController->GetBlackBoardComponent()->SetValueAsVector("SpawnLocation", GetActorLocation());
		}
	}
}

void ASpawnEnemyManager::CreateEnemy()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WORLD NULL"));
		return;
	}

	if (CurrentEnemyToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentEnemyToSpawn null"));
		return;
	}

	if (SpawnLocation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnLocation null"));
		return;
	}

	AAIEnemyCharacter* EnemyCharacter = World->SpawnActor<AAIEnemyCharacter>(
		CurrentEnemyToSpawn, SpawnLocation->GetComponentLocation(), GetActorRotation());
	SetupEnemy(EnemyCharacter);
	EnemiesSpawned.Add(EnemyCharacter);
}

void ASpawnEnemyManager::SpawnEnemy(int Delay)
{
	FTimerHandle handle;

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WORLD NULL"));
		return;
	}

	if (bIsFirstSpawn)
	{
		bIsFirstSpawn = false;

		//spawned 2 enemies
		for (int i = 0; i < 2; i++)
		{
			CreateEnemy();
		}
	}

	GetWorldTimerManager().SetTimer(handle, [this]()
	{
		CreateEnemy();
	}, Delay, false);

	AllSpawnTimer.Add(handle);
}

void ASpawnEnemyManager::DeleteAI(AAIEnemyCharacter* AIToDelet)
{
	//if an enemy touch this box collision, that means it's getting back to the spawner
	//we delete this one and remove it from the instanciated array
	EnemiesSpawned.Remove(AIToDelet);
	AIToDelet->Destroy();

	//check if the array is empty : true -> no more IA in the maps -> we need to instanciate one immediately
	if (EnemiesSpawned.Num() == 0)
	{
		CreateEnemy();
	}
		//else : we wait a random delay between 0 and 5s
	else
	{
		int NewDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
		if (NewDelay == 0)
		{
			CreateEnemy();
		}
		else
		{
			SpawnEnemy(NewDelay);
		}
	}
}

void ASpawnEnemyManager::DeleteBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ASpawnEnemyManager::StopAllTimeHandle()
{
	for (FTimerHandle Handle : AllSpawnTimer)
	{
		UE_LOG(LogTemp, Log, TEXT("Invalidate handle"));
		GetWorldTimerManager().ClearTimer(Handle);
	}
}
