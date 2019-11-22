// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKSASSETS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float ElevateSpeed); //Elevate speed: -1 is down, +1 is up

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinHeightDegrees = 0;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxHeightDegrees = 30;
};
