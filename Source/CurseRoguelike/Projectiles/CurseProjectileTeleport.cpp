// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileTeleport.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"

ACurseProjectileTeleport::ACurseProjectileTeleport() {}

void ACurseProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACurseProjectileTeleport::OnHit);
	CollisionComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ACurseProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	// ‘Explodes’ after 0.2 seconds. -- teleport instigator to the current projectile location.
}

void ACurseProjectileTeleport::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{}

void ACurseProjectileTeleport::TeleportInstigator(const FTransform& Transform)
{
	// TODO: Determine teleport location based on whether landscape or other object was hit. Landscapes do not support de-penetration on teleport, so we need to find a suitable location.
	//   Do it like so:
	//   - Overlap instigator at the hit location
	//   - See the relative transform of the capsule vs the overlap results
	//   - Correct the location
	//   - Repeat until suitable location is found, or until max attempts reached

	// Play particle effect at point of detonation.
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportEffect, Transform.GetLocation(), Transform.GetRotation().Rotator());

	// Make sure you ‘stop’ the projectile movement while you wait
	ProjectileMovementComponent->StopMovementImmediately();

	// Waits 0.2 seconds again (Timer) before Teleporting PlayerCharacter (aka the ‘Instigator’ of the projectile)
	// - Lets the detonation effect play a little bit before we teleport so player can see it.

	// After the wait:
	// - Teleport the instigator
	// - Destroy the projectile
}
