// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKSASSETS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle); 
	
	// Max Force to Track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float MaxAcceleration = 40000000.f;
};
