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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle); 
	
	// Max Force to Track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float MaxAcceleration = 40000000.f;

private:
	UTankTrack();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
