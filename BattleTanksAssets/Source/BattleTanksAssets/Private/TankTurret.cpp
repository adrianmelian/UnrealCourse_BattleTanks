// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTurret.h"

void UTankTurret::RotateY(float RotateSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("RotateY being called"));
	RotateSpeed = FMath::Clamp<float>(RotateSpeed, -1.f, 1.f); // In case ElevateSpeed > 1 or < -1
	float RotateChange = (RotateSpeed * MaxDegreesPerSecond) * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotateChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
