// Copyright 2019, ProskPetr, All rights reserved.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)Health / (float)MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageToApply = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, Health);

	Health -= DamageToApply;
	if (Health == 0)
	{
		OnHealthEnd.Broadcast();
	}

	return DamageToApply;
}