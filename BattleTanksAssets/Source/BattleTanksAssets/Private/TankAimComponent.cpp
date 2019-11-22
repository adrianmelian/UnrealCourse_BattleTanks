// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "tankBarrel.h"
#include "TankAimComponent.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutTossVelocity;
	FVector BarrelLoc = Barrel->GetSocketLocation(FName("Projectile") );
	TArray< AActor* > actorsToSkip;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutTossVelocity, BarrelLoc, HitLocation, LaunchSpeed, 0, 0, ESuggestProjVelocityTraceOption::TraceFullPath);
	if (bHaveAimSolution)
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: aiming solution found!"), Time);
		FVector LaunchNormal = OutTossVelocity.GetSafeNormal();
		AimBarrelAt(LaunchNormal);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: aiming solution not found"), Time);
	}
}

void UTankAimComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimComponent::AimBarrelAt(FVector AimDirection)
{
	// Get current rotation of barrel
	// Move barrel towards aimDirection
	auto CurrentBarrelRot = Barrel->GetForwardVector().Rotation();
	auto AimToRot = AimDirection.Rotation();
	auto DeltaRot = AimToRot - CurrentBarrelRot;
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimToRot.ToString());

	Barrel->Elevate(5.f);
}


