// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();	// Calls parent class
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Not Possesing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Possesing %s"), *(ControlledTank->GetName()));
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

	FVector HitLocation; // Out parameter
	
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get World Location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{	
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}	
	return true;
}

// "De-project" the ScreenLocation of the crosshair to a LookDirection
// LookDirection is unit vector. 
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	// if we hit anything visible within range, set it's hit location and return true
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
	)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	// otherwise set hit location to 0 and return false
	HitLocation = FVector(0.0f);
	return false; //Line trace didn't succeed
}
