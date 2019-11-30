// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Particles"));
	LaunchBlast->AttachTo(RootComponent);

	// Adding required Aiming Component
	ProjectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Move Component"));
	ProjectileMoveComponent->bAutoActivate = false;
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Immpact Blast Particles"));
	//ImpactBlast->AttachTo(RootComponent);
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float Speed)
{
	
	ProjectileMoveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMoveComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ImpactBlast->Activate();
	LaunchBlast->Deactivate();
	ExplosionForce->FireImpulse();
	//CollisionMesh->SetSimulatePhysics(true);
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent(true);
}