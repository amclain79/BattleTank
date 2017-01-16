// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last #include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;	// const means reference connot alter controlled tank
	
	virtual void BeginPlay() override;	// virtual means children can override (append) function
										// BeginPlay() is an AActor method
	virtual void Tick(float DeltaTime) override;	

	void AimTowardsCrosshair();	// Moves barrel to crosshair

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const; // return location of where we would hit in landscape

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;

};
