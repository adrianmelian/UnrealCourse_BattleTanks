// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
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
	ImpactBlast->Activate(); // Turn on hit explosion
	LaunchBlast->Deactivate(); // Turn off trailing smoke
	ExplosionForce->FireImpulse(); // Apply force to hit actor

	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, TSubclassOf<UDamageType>(), TArray<AActor*>());

	CollisionMesh->SetSimulatePhysics(true); // <- To have rolling cannon ball after hit
	
	// Uncomment if you want the Projectile to disappear after hit
	//SetRootComponent(ImpactBlast); 
	//CollisionMesh->DestroyComponent(true);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpired, DestroyDelay, false);
}

void AProjectile::OnTimerExpired()
{
	Destroy();
}