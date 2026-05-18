// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileTeleport.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Constraint.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
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

	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ACurseProjectileTeleport::OnTimeExpired, TeleportDelay);
}

void ACurseProjectileTeleport::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TeleportTimerHandle);

	TeleportInstigator(FTransform{GetActorQuat(), Hit.ImpactPoint});
}

void ACurseProjectileTeleport::OnTimeExpired()
{
	TeleportInstigator(GetActorTransform());
}

void ACurseProjectileTeleport::TeleportInstigator(const FTransform& Location)
{
	APawn* Instigator = GetInstigator();
	if (!IsValid(Instigator))
	{
		return;
	}

	// TODO: Determine teleport location based on whether landscape or other object was hit. Landscapes do not support de-penetration on teleport, so we need to find a suitable location.
	//   Do it like so:
	//   - Overlap instigator at the hit location
	//   - See the relative transform of the capsule vs the overlap results
	//   - Correct the location
	//   - Repeat until suitable location is found, or until max attempts reached
	TeleportLocation = Location;

	// Stop playing the loops.
	LoopedEffectComponent->DeactivateImmediate();
	LoopedAudioComponent->Stop();

	// Play particle effect at point of detonation.
	UNiagaraComponent* ParticleEffect =
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportEffect, Location.GetLocation(), Location.GetRotation().Rotator());

	// Play teleport sound at point of detonation.
	UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, Location.GetLocation());

	// Stop the projectile movement while the effect plays.
	ProjectileMovementComponent->StopMovementImmediately();

	// Set a timer to handle teleportation after the effect finishes.
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ACurseProjectileTeleport::OnTeleportFinished, TeleportEffectTime);
}

void ACurseProjectileTeleport::OnTeleportFinished()
{
	APawn* Instigator = GetInstigator();
	if (IsValid(Instigator))
	{
		Instigator->TeleportTo(TeleportLocation.GetLocation(), TeleportLocation.GetRotation().Rotator());
	}
	// After the wait:
	// - Teleport the instigator
	// - Destroy the projectile

	Destroy();
}
