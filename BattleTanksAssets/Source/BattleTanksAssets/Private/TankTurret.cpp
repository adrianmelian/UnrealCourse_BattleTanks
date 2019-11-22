// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTurret.h"

void UTankTurret::RotateY(float RotateSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("RotateY being called"));
	RotateSpeed = FMath::Clamp<float>(RotateSpeed, -1.f, 1.f); // In case ElevateSpeed > 1 or < -1
	float RotateChange = (RotateSpeed * MaxDegreesPerSecond) * GetWorld()->DeltaTimeSeconds;
	float RawNewRotate = RelativeRotation.Yaw + RotateChange;
	//float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinHeightDegrees, MaxHeightDegrees); // in case ElevateSpeed > 1 or < -1
	SetRelativeRotation(FRotator(0, RawNewRotate, 0));
}
