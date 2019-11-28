// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimComponent.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTime)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (BarrelIsMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}
}

void UTankAimComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutTossVelocity;
	FVector BarrelLoc = Barrel->GetSocketLocation(FName("Projectile") );
	//bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutTossVelocity, BarrelLoc, HitLocation, LaunchSpeed); // This caused very weird behaviour which below fixed
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutTossVelocity,
		BarrelLoc,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutTossVelocity.GetSafeNormal();
		AimBarrelAt();
	}
}

void UTankAimComponent::AimBarrelAt()
{
	if (!ensure(Barrel && Turret)) { return; }
	// Get current rotation of barrel
	// Move barrel towards aimDirection
	auto CurrentBarrelRot = Barrel->GetForwardVector().Rotation();
	auto AimToRot = AimDirection.Rotation();
	auto DeltaRot = AimToRot - CurrentBarrelRot;

	Barrel->Elevate(DeltaRot.Pitch);
	Turret->RotateY(DeltaRot.Yaw);
}

bool UTankAimComponent::BarrelIsMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // If vectors are equal withing tolerance
}

void UTankAimComponent::Fire()
{
	bool isLoaded((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime);
	if (FiringStatus != EFiringStatus::Reloading)
	{
		if (!ensure(ProjectileBP)) { return; }
		if (!ensure(Barrel)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}