// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemyManager.generated.h"

/*
 *
 
Lorsque la partie commence, 2 IAs arrivent directement dans la salle en apportant des aliments.
Une 3ème IA arrive 1 minute après le début de la partie.
Lorsqu’une IA sort de la salle, une autre IA arrive entre 0 et 5s après.
Si à la sortie d’une IA aucune autre IA n’est présente dans la salle, alors l’IA qui devrait suivre arrive immédiatement.

 * 
 */

UCLASS()
class DUNGEONSTHIEF_API ASpawnEnemyManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	;
	class UBoxComponent* DeleteEnemyBoxComponent;

	//The object is placed in such a way that the enemies do not touch the collision box when they are instantiated
	UPROPERTY(VisibleAnywhere)
	;
	class USphereComponent* SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Spawn Enemy")
	TSubclassOf<class AAIEnemyCharacter> FirstEnemyToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn Enemy")
	TSubclassOf<class AAIEnemyCharacter> SecondEnemyToSpawn;

	TSubclassOf<class AAIEnemyCharacter> CurrentEnemyToSpawn;

	TArray<class AAIEnemyCharacter*> EnemiesSpawned;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Enemy")
	float MinSpawnDelay;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Enemy")
	float MaxSpawnDelay;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Enemy")
	int FirstSpawnDelay;

	bool bIsFirstSpawn;

	bool bGlobalWaitAI;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DeleteAI(AAIEnemyCharacter* AIToDelet);

	FORCEINLINE TArray<class AAIEnemyCharacter*> GetEnemiesSpawned() { return EnemiesSpawned; }

	FORCEINLINE bool GetGlobalWaitAI() { return bGlobalWaitAI; }
	FORCEINLINE void SetGlobalWaitAI(bool value) { bGlobalWaitAI = value; }

	UFUNCTION()
	void StopAllTimeHandle();

protected:
	TArray<FTimerHandle> AllSpawnTimer;

	void SetupEnemy(class AAIEnemyCharacter* EnemyCharacter);

	void CreateEnemy();

	void SpawnEnemy(int Delay);

	UFUNCTION()
	virtual void DeleteBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
