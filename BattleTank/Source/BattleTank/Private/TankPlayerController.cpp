// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{	
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController doesn't possese a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has Tank: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation), (ViewportSizeY * CrossHairYLocation));

	/// De-project the screen position of the crosshair to a look direction
	FVector LookDirection; // OUT
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/// Take look direction and get HitLocation
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector WorldLocation; // OUT. Not using, just for function
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult OutHit;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			OutHit,
			LineTraceStart,
			LineTraceEnd,
			ECollisionChannel::ECC_Visibility
		))
	{
		OutHitLocation = OutHit.Location;
		
		return true;
	}

	return false;
}