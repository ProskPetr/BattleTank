// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// How close can AI tank get to the player
	float AcceptanceRadius = 3000.0;

	APawn* ControlledTank = nullptr;

};
