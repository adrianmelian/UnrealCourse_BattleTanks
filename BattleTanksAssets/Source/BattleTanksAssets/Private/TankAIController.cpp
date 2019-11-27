// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimComponent.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // Get Player
	auto ControlledTank = GetPawn(); // Get Self

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move Towards player
	MoveToActor(PlayerTank, AccecptanceRadius);
	
	// Aim at player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimComponent>(); // Get Access to component on self
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	// AimingComponent->Fire();

}