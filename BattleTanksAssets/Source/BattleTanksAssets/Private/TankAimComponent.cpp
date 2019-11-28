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
	if (GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTime)
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
		FVector LaunchNormal = OutTossVelocity.GetSafeNormal();
		AimBarrelAt(LaunchNormal);
	}
}

void UTankAimComponent::AimBarrelAt(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	// Get current rotation of barrel
	// Move barrel towards aimDirection
	auto CurrentBarrelRot = Barrel->GetForwardVector().Rotation();
	auto AimToRot = AimDirection.Rotation();
	auto DeltaRot = AimToRot - CurrentBarrelRot;
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimToRot.ToString());

	Barrel->Elevate(DeltaRot.Pitch);
	Turret->RotateY(DeltaRot.Yaw);
}

void UTankAimComponent::Fire()
{
	bool isLoaded((FPlatformTime::Seconds() - LastFireTime) > ReloadTime);
	if (FiringStatus != EFiringStatus::Reloading)
	{
		if (!ensure(ProjectileBP)) { return; }
		if (!ensure(Barrel)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}