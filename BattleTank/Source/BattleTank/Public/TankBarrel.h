// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


// Holds Elevate method and Barrel properties
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float MoveSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0.0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 30.0;
};
