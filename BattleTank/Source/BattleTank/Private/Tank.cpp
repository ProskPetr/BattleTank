// Copyright 2019, ProskPetr, All rights reserved.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageToApply = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, Health);

	Health -= DamageToApply;
	if (Health == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank destroyed."));
	}

	return DamageToApply;
}