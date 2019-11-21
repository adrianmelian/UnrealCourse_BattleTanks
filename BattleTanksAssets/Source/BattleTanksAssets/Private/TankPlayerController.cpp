// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing tank"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *ControlledTank->GetName());
	{
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
	if (!GetControlledTank()) { return; }

	FVector HitLoc; // OUT Parameter created here and passed as reference. Which will be changed by GetSightRayHitLocation()
	if (GetSightRayHitLocation(HitLoc))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Locaiton: %s"), *HitLoc.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLoc) const
{

	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);

	auto ScreenLocation = FVector2D(ViewportX * ReticuleXLoc, ViewportY * ReticuleYLoc);

	OutHitLoc = FVector(0.f);
	return true;
}
