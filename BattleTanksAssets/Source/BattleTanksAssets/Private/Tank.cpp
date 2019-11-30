// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartHealth;
}

float ATank::GetHeathPercent()
{
	return (float)CurrentHealth / (float)StartHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	int32 DamageInt = FMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp<int>(DamageInt, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %i"), CurrentHealth);
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return 0.0f;
}
