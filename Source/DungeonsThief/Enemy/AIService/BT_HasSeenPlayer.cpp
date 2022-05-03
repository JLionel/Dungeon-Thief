// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_HasSeenPlayer.h"

#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonsThief/Player/MainCharacter.h"

void UBT_HasSeenPlayer::CodeToExecute()
{
	Super::CodeToExecute();
	//Line to the player -> PlayerPos - Enemy
	//Normalize that
	//GetForward from enemy
	//Calculate the dot product between forward and the line
	//Use ACos(degrees) from the dot result
	//Check if this is less than a certain amount

	// If true : AI can see player
	// else : AI can't see player

	FVector EnemyLocation = AIController->GetPawn()->GetActorLocation();
	FVector PlayerLocation = FVector::ZeroVector;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		PlayerLocation = PlayerPawn->GetActorLocation();
	}

	FVector LineToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();
	FVector EnemyForward = AIController->GetPawn()->GetActorForwardVector();

	float DotProduct = FVector::DotProduct(LineToPlayer, EnemyForward);
	float ACos = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	FVector StartTrace = EnemyLocation + EnemyForward * 2;
	AActor* IgnoreActor = AIController->GetPawn();

	//The enemy has seen the player and he's in sight : the enemy start chasing him
	if (ACos < AIController->GetFieldOfView() && CanSeePlayerRayCast(LineToPlayer, StartTrace,
	                                                                 AIController->GetSightDistance(), IgnoreActor))
	{
		uint8 byteEnum = static_cast<uint8>(EEnemyState::EES_Chasing);
		BlackboardComponent->SetValueAsEnum("EnemyState", byteEnum);
		BlackboardComponent->SetValueAsVector("PlayerLocation", PlayerLocation);

		AIController->SetEnemyState(EEnemyState::EES_Chasing);

		AICharacter->SetHasSeenPlayer(true);
		AICharacter->SetIsInSight(true);
	}
	else
	{
		AICharacter->SetIsInSight(false);
	}

	//The enemy has seen the player but he's not in sight anymore : the enemy'll wander to the last player's position known
	if (AICharacter->GetHasSeenPlayer() && !AICharacter->GetIsInSight())
	{
		uint8 ByteEnum = static_cast<uint8>(EEnemyState::EES_Wandering);
		BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);

		AIController->SetEnemyState(EEnemyState::EES_Wandering);
		AICharacter->SetWanderCooldown();
	}

	//We reset the enemy state with the one before it has seen the player
	if (!AICharacter->IsInWanderCooldown() && !AICharacter->GetHasSeenPlayer())
	{
		uint8 ByteEnum = static_cast<uint8>(EEnemyState::EES_Patrolling);
		BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);

		AIController->SetEnemyState(EEnemyState::EES_Patrolling);
	}
}

bool UBT_HasSeenPlayer::CanSeePlayerRayCast(FVector ForwardVector, FVector StartTrace, float MaxDistance,
                                            AActor* IgnoreActor)
{
	FHitResult* HitResult = new FHitResult();
	FVector EndTrace = StartTrace + (ForwardVector * MaxDistance);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(IgnoreActor);

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_WorldStatic, *TraceParams))
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(HitResult->GetActor());

		//If the MainCharacter is valid, nothing is between the enemy and the player. The enemy can keep chasing the player
		return MainCharacter == nullptr ? false : true;
	}

	return false;
}
