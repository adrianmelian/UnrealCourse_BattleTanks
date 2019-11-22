// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKSASSETS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

public:
	void RotateY(float RotateSpeed); // Rotate speed: -1 is Left, +1 is Right
};
