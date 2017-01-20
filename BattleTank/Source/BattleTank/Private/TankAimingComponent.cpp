// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// Protect Barrel reference
	if (!Barrel) { return; }

	UObject* WorldContextObject = this;
	FVector OutLaunchVelocity;
	// Reference Projectile socket on tank_fbx_Barrel 
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHighArc = false; // favor the lower arc.
	float CollisionRadius = 0.0f; //Radius of the projectile (assumed spherical), used when tracing
	float OverrideGravityZ = 0; // do not override
	const FCollisionResponseParams ResponseParam; //ignoring
	const TArray < AActor * > ActorsToIgnore;	  //ignoring
	bool bDrawDebug = false; // no debug line
	// Calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
				WorldContextObject,
				OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				bHighArc,
				CollisionRadius,
				OverrideGravityZ,
				ESuggestProjVelocityTraceOption::DoNotTrace,
				ResponseParam,
				ActorsToIgnore,
				bDrawDebug))
	{
		// Convert OutLaunchVelocity to unit vector
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
	}
}