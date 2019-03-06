// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		auto ControlledTank = Cast<ATank>(GetPawn());

		// TODO Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check if AcceptanceRadius is in cm
		
		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		// TODO remove comment later
		// ControlledTank->Fire();
	}
}
