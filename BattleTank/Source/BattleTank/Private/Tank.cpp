// Copyright 2 Real Studios

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	// protect pointer
	if (!TankAimingComponent) { return; }
	//Delegate to TankAimingComponent
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);	
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{ 
		// Spawn a projectile at the socket location on the barrel
		FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);

		// Use LaunchSpeed to launch the projectile
		Projectile->LaunchProjectile(LaunchSpeed);

		// Record the fire time
		LastFireTime = FPlatformTime::Seconds();
	}
}