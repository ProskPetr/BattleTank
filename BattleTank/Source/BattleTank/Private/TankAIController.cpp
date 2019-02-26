// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController doesn't possese a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has Tank: %s"), *(ControlledTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPlayerTank())
	{
		// TODO Move towards the player
		
		// Aim at the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerTank = nullptr;
	PlayerTank = GetWorld()->GetFirstPlayerController();

	return Cast<ATank>(PlayerTank->GetPawn());
}