// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
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

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank)) { return; }

	// Move Towards player
	MoveToActor(PlayerTank, AccecptanceRadius);
	// Aim at player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();

}