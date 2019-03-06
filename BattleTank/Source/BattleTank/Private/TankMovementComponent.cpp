// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *(GetOwner()->GetName()), *(MoveVelocity.ToString()));
}

void UTankMovementComponent::MoveForward(float Speed)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Speed);
	RightTrack->SetThrottle(Speed);
}

void UTankMovementComponent::TurnRight(float Speed)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Speed);
	RightTrack->SetThrottle(-Speed);
}

