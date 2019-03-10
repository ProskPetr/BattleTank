// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on TankMovementComponent via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
		
	// Aim towards the player
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}	
}
