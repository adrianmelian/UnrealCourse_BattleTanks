// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKSASSETS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Called at Init
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// How close the ai tank can get to player
	float AccecptanceRadius = 100.f;
};
