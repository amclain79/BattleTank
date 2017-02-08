// Copyright 2 Real Studios

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Responsible for helping the AI aim.
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	// How close the AI tank can get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000; // 80 meters

private:
	virtual void BeginPlay() override;	// virtual means children can override (append) function
										// BeginPlay() is an AActor method	
	// method called by unreal when AI tank becomes possessed
	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTankDeath();
};
