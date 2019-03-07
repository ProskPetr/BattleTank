// Copyright 2019, ProskPetr, All rights reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

// Forward Declarations
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UTankBarrel* Barrel = nullptr; // TODO remove later

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	double LastTimeFired = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3; // In seconds		
	
};
