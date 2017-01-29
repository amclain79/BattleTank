// Copyright 2 Real Studios

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	//Prevent launch of projectile upon spawning
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
	// Projectile Rotation set from Barrel Rotation in ATank::Fire(), thus, its forward vector is
	// the same as the Barrel when spawned.
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	// Launch
	ProjectileMovement->Activate();
}