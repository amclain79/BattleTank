// Copyright 2 Real Studios

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a relative elevation speed between -1 and 1 and the frame time
	// Clamp relative speed between -1 and 1
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSecond;
	// Make frame rate independent
	ElevationChange = ElevationChange * GetWorld()->DeltaTimeSeconds;
	// Get unclamped elevation
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	// Clamp new elevation between MaxElevationDegrees and MinElevationDegrees
	auto ClampedRawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedRawNewElevation,0,0));
}


