// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "TankAimComponent.h"
#include "CollisionQueryParams.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimCompRef = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimCompRef)) { return; }
	FoundAimingComponent(AimCompRef);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsReticule();
}

void ATankPlayerController::AimTowardsReticule()
{
	if (!GetPawn()) { return; } // If not possessing

	auto AimCompRef = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimCompRef)) { return; }

	FVector OutHitLocation; // OUT Parameter
	if (GetSightRayHitLocation(OutHitLocation))
	{
		AimCompRef->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Get screen location in 2D pixels
	int32 ViewportX, ViewportY; // OUT Parameters
	GetViewportSize(ViewportX, ViewportY);
	FVector2D ScreenLocation = FVector2D(ViewportX * ReticuleXLoc, ViewportY * ReticuleYLoc);

	FVector LookDirection; // OUT Parameter
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitDirection(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldDirection; // To be discarded, required for DeprojectScreenPositionToWorld
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldDirection, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0);
	return false;
}
