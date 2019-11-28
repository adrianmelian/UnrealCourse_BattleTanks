// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move Towards player
	MoveToActor(PlayerTank, AccecptanceRadius);
	
	// Aim at player
	auto AimCompRef = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimCompRef->AimAt(PlayerTank->GetActorLocation());

	AimCompRef->Fire();

}