// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANKSASSETS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Cast Pawn to ATank Class 
	ATank* GetControlledTank() const;
	ATank* ControlledTank;

	// Move Barrel towards reticule
	void AimTowardsReticule();
	bool GetSightRayHitLocation(FVector& OutHitLoc) const;

	// Getting Look direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Get vector Hit Location
	bool GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const;

	// Reticule Position. If changed also change reticule position in UI 
	UPROPERTY(EditAnywhere)
	float ReticuleXLoc = 0.5f;
	UPROPERTY(EditAnywhere)
	float ReticuleYLoc = 0.35f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000000.f;

};
