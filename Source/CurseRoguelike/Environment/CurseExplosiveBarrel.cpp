// Copyright 2026 Andrzej Haczewski.

#include "CurseExplosiveBarrel.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"

ACurseExplosiveBarrel::ACurseExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	ExplosionForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForceComp"));
	ExplosionForceComponent->SetupAttachment(MeshComponent);
	ExplosionForceComponent->ImpulseStrength = 250000.f;
	ExplosionForceComponent->Radius = 500.f;
	ExplosionForceComponent->Falloff = RIF_Linear;
	ExplosionForceComponent->bAutoActivate = false;
	ExplosionForceComponent->bIgnoreOwningActor = true;
}

float ACurseExplosiveBarrel::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0 && !bIsExploded)
	{
		// Start burning and explode after BurningDuration.
		if (!bIsBurning)
		{
			bIsBurning = true;

			BurningEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				BurningEffect,
				ExplosionForceComponent,
				NAME_None,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::Type::SnapToTarget,
				true);
			BurningSoundComponent = UGameplayStatics::SpawnSoundAttached(
				BurningSound,
				ExplosionForceComponent,
				NAME_None,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::Type::SnapToTarget,
				true);

			GetWorldTimerManager().SetTimer(BurningTimerHandle, this, &ACurseExplosiveBarrel::Explode, BurningDuration, false);
		}
		// Explode immediately, invalidating explosion timer.
		else
		{
			if (BurningTimerHandle.IsValid())
			{
				GetWorldTimerManager().ClearTimer(BurningTimerHandle);
			}
			
			Explode();
		}
	}

	return ActualDamage;
}

void ACurseExplosiveBarrel::Explode()
{
	ExplosionForceComponent->FireImpulse();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, ExplosionForceComponent->GetComponentLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, ExplosionForceComponent->GetComponentLocation());

	if (IsValid(BurningEffectComponent)) BurningEffectComponent->Deactivate();
	if (IsValid(BurningSoundComponent)) BurningSoundComponent->Stop();

	bIsBurning = false;
	bIsExploded = true;

	// Destroy();
	// MeshComponent->SetSimulatePhysics(false);
	// MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// MeshComponent->SetHiddenInGame(true);
	// SetLifeSpan(1.f);
}
