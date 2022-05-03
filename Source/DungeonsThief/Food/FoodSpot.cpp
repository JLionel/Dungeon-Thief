// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodSpot.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AFoodSpot::AFoodSpot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	SpotMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spot");
	SpotMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(SpotMesh);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFoodSpot::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AFoodSpot::OnBoxOverlapEnd);

	SpawnSceneComponent = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnSceneComponent->SetupAttachment(SpotMesh);

	SpotParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpotParticles"));
	SpotParticles->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFoodSpot::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AFoodSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFoodSpot::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	ACarryingCharacter* Player = Cast<ACarryingCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetSpotReference(this);
	Player->SetIsNearSpot(true);
}

void AFoodSpot::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACarryingCharacter* Player = Cast<ACarryingCharacter>(OtherActor);
	if (Player == nullptr)
	{
		//Overlap actor isn't the player
		return;
	}

	Player->SetSpotReference(nullptr);
	Player->SetIsNearSpot(false);
}
