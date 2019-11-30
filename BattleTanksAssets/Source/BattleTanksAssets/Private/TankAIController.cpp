// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankAimComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Ams Dyied"));
	PossessedTank->DetachFromControllerPendingDestroy();
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

	// If aiming or locked
	if (AimCompRef->GetFiringStatus() == EFiringStatus::Ready)
	{
		AimCompRef->Fire();
	}

}

