// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");
	RootComponent = FoodMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(FoodMesh);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFood::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AFood::OnBoxOverlapEnd);


	bIsOnSpot = false;
}

void AFood::BeTake()
{
	UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
	FoodMesh->SetSimulatePhysics(false);
	FoodMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void AFood::BeDrop()
{
	//befor applying in the project for the food, ignore the pawn only to make the game more fluid

	FoodMesh->SetSimulatePhysics(true);
	FoodMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	FoodMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//FoodMesh->SetCollisionProfileName("OverlapOnlyPawn");
}


// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	SetRandomMesh();

	FoodMesh->SetSimulatePhysics(true);
	FoodMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	FoodMesh->SetMassScale(NAME_None, 10);
	BecomeSuperFood();
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/**
 * @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
 */
void AFood::SetRandomMesh()
{
	//Choose random index
	int MeshIndex = FMath::FRandRange(0, FoodArray.Num());

	if (FoodMesh == nullptr)
	{
		return;
	}

	FoodMesh->SetStaticMesh(FoodArray[MeshIndex]);
}

void AFood::BecomeSuperFood()
{
	int LuckySuperFNumber = FMath::FRandRange(0, SuperFoodRate + 1);

	if (LuckySuperFNumber == 5)
	{
		FoodPoints = 2;
		SpeedReduction = 0.25;
		FoodMesh->SetStaticMesh(SuperFoodMesh);
		SetActorScale3D(FVector::OneVector * 0.85f);
		IsSuperFood = true;
	}
}

void AFood::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	ACarryingCharacter* Player = Cast<ACarryingCharacter>(OtherActor);

	if (Player == nullptr)
	{
		//OverlapActor isn't the player
		return;
	}

	Player->SetNearFoodActor(this);
}

void AFood::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACarryingCharacter* Player = Cast<ACarryingCharacter>(OtherActor);

	if (Player == nullptr)
	{
		//OverlapActor isn't the player
		return;
	}

	Player->SetNearFoodActor(nullptr);
}
