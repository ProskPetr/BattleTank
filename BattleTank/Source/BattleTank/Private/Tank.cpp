// Copyright 2019, ProskPetr, All rights reserved.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("PENDOR: Tank C++ Construct"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Necessary to run BP BeginPlay

	UE_LOG(LogTemp, Warning, TEXT("PENDOR: Tank C++ BeginPlay"));
}

void ATank::AimAt(FVector HitLocation)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}	
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTime;
	
	if (Barrel && bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastTimeFired = FPlatformTime::Seconds();
	}
}