// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"	// Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	// Creates a method that we can call via tank blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

protected: // Need to access via UPROPERTY, but not part of tank interface
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;	
	
};
