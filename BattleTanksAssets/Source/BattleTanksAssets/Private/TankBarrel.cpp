// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float ElevateSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("DPS: %f"), ElevateSpeed);
	ElevateSpeed = FMath::Clamp<float>(ElevateSpeed, -1.f, 1.f); // In case ElevateSpeed > 1 or < -1
	float ElevationChange = (ElevateSpeed * MaxDegreesPerSecond) * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinHeightDegrees, MaxHeightDegrees); // in case ElevateSpeed > 1 or < -1
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}