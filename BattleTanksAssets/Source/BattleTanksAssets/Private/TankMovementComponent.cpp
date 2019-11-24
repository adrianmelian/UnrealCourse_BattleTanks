// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet)
{
	LTrack = LTrackToSet;
	RTrack = RTrackToSet;
}



void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LTrack || !RTrack) { return; }
	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float TurnAmount)
{
	if (!LTrack || !RTrack) { return; }
	LTrack->SetThrottle(TurnAmount);
	RTrack->SetThrottle(-TurnAmount);
}


