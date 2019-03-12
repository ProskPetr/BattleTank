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

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 MaxHealth = 100.0;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 Health = MaxHealth;
};
