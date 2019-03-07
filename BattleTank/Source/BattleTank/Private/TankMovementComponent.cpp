// Copyright 2019, ProskPetr, All rights reserved.

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
	auto ForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto MoveForwardRelativeVelocity = FVector::DotProduct(AIForwardIntention, ForwardVector);
	auto TurnRightRelativeVelocity = FVector::CrossProduct(ForwardVector, AIForwardIntention).Z;

	MoveForward(MoveForwardRelativeVelocity);
	TurnRight(TurnRightRelativeVelocity);
}

void UTankMovementComponent::MoveForward(float RelativeVelocity)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(RelativeVelocity);
	RightTrack->SetThrottle(RelativeVelocity);
}

void UTankMovementComponent::TurnRight(float RelativeVelocity)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(RelativeVelocity);
	RightTrack->SetThrottle(-RelativeVelocity);
}

