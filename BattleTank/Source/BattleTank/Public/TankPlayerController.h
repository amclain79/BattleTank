// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last #include

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected: //so that the subclass blueprint can access
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;	// const means reference connot alter controlled tank

private:
	virtual void BeginPlay() override;	// virtual means children can override (append) function
										// BeginPlay() is an AActor method
	virtual void Tick(float DeltaTime) override;	

	void AimTowardsCrosshair();	// Moves barrel to crosshair

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const; // return location of where we would hit in landscape

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f; // cm (10km)

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


};
