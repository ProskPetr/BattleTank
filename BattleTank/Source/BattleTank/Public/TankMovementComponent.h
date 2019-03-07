// Copyright 2019, ProskPetr, All rights reserved.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
Used for player and AI tanks movement
**/
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Custom))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(float RelativeVelocity);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void TurnRight(float RelativeVelocity);
	
private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
