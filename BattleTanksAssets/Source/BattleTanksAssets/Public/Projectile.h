// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKSASSETS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void Launch(float Speed);

private:
	UProjectileMovementComponent* ProjectileMoveComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
};
