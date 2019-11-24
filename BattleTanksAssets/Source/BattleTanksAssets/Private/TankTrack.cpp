// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PrimitiveComponent.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving at speed: %f"), Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * MaxAcceleration;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
