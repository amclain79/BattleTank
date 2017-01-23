// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers added in constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	// Delegate moving the barrel
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	// set local reference for spawning projectile
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	// Delegate
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	//Delegate to TankAimingComponent
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);	
}

void ATank::Fire()
{
	if (!Barrel) { return; }

	// Spawn a projectile at the socket location on the barrel
	FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);

	// Use LaunchSpeed to launch the projectile
	Projectile->LaunchProjectile(LaunchSpeed);
}