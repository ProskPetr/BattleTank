// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::Move(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s speed %f"), Time, *(this->GetName()), Speed);

	auto ForceApplied = GetForwardVector() * Speed * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}

