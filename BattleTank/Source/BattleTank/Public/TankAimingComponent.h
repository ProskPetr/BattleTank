// Copyright 2019, ProskPetr, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Holds barrel's properties and Elevate method
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup = (Custom))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsBarrelMoving();

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	FVector AimDirection;

	void MoveBarrelTowards();

	double LastTimeFired = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3; // In seconds		

};
