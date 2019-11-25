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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need for Super, because we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto RequestedMoveVector = MoveVelocity.GetSafeNormal();
	
	auto ForwardVector = FVector::DotProduct(TankForward, RequestedMoveVector);
	IntendMoveForward(ForwardVector);

	auto TurnVector = FVector::CrossProduct(RequestedMoveVector, TankForward);
	IntendTurnRight(TurnVector.Z);

	//UE_LOG(LogTemp, Warning, TEXT("%s MoveVelocity = %s"),*Name, *MoveVelocityString) ;
}


