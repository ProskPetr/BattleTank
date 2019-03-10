// Copyright 2019, ProskPetr, All rights reserved.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastTimeFired = FPlatformTime::Seconds(); // To make first shot after reload
	Ammo = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (((FPlatformTime::Seconds() - LastTimeFired) < ReloadTime) && !IsOutOfAmmo())
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving() && !IsOutOfAmmo())
	{
		FiringState = EFiringState::Aiming;
	}
	else if (IsOutOfAmmo())
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsOutOfAmmo()
{
	return Ammo == 0;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Param must be here to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForwardVector = Barrel->GetForwardVector().GetSafeNormal();
	return !BarrelForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Turret && Barrel)) { return; }

	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	bool bReadyToFire = (FiringState != EFiringState::Reloading) && !IsOutOfAmmo();

	if (bReadyToFire)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastTimeFired = FPlatformTime::Seconds();
		Ammo--;
	}
}