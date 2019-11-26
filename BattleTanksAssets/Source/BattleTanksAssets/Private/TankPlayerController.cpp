// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine/World.h"
#include "TankAimComponent.h"
#include "CollisionQueryParams.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimCompRef = GetControlledTank()->FindComponentByClass<UTankAimComponent>();
	if (AimCompRef) 
	{
		FoundAimingComponent(AimCompRef);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller cannot fiind Aiming Component"));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsReticule();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsReticule()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector OutHitLocation; // OUT Parameter
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
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
		GetLookVectorHitDirection(LookDirection, OutHitLocation);
	}

	//OutHitLocation = FVector(0.f);
	return true;
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
