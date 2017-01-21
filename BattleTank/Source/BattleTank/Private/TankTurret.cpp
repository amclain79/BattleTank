// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Clamp relative speed between -1 and 1
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond;
	// Make frame rate independent
	RotationChange = RotationChange * GetWorld()->DeltaTimeSeconds;
	// Get unclamped Rotation
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator( 0, Rotation, 0));
}


