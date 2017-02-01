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
	
private:
	virtual void BeginPlay() override;	// virtual means children can override (append) function
										// BeginPlay() is an AActor method	
	virtual void Tick(float DeltaTime) override;

	// How close the AI tank can get to player
	float AcceptanceRadius = 3000;
};
