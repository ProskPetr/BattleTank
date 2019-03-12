// Copyright 2019, ProskPetr, All rights reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

private:
	ATank();

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 Health = 100.0;
};
