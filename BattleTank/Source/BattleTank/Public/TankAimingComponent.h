// Copyright 2019, ProskPetr, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declarations
class UTankBarrel; 
class UTankTurret;

// Holds barrel's properties and Elevate method
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup = (Custom))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

};
