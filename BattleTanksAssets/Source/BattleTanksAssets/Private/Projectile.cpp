// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Particles"));
	LaunchBlast->AttachTo(RootComponent);

	// Adding required Aiming Component
	ProjectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Move Component"));
	ProjectileMoveComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), Speed);
	ProjectileMoveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMoveComponent->Activate();
}
