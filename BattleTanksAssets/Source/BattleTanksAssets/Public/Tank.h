// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;
class UTankAimComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANKSASSETS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UTankAimComponent* TankAimComponent = nullptr;
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP = nullptr;

	UTankBarrel* Barrel = nullptr;


	double LastFireTime = 0;
public:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 2.5;

	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();
	
	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; // TODO Find good default value

};
