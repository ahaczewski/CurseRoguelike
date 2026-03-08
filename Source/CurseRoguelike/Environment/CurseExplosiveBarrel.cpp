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

	ExplosionForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForceComp"));
	ExplosionForceComponent->SetupAttachment(MeshComponent);
	ExplosionForceComponent->ImpulseStrength = 250000.f;
	ExplosionForceComponent->Radius = 500.f;
	ExplosionForceComponent->Falloff = RIF_Linear;
	ExplosionForceComponent->bAutoActivate = false;

	LoopedBurningEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedBurningEffectComp"));
	LoopedBurningEffectComponent->SetupAttachment(MeshComponent);
	LoopedBurningEffectComponent->bAutoActivate = false;

	LoopedBurningSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedBurningSoundComp"));
	LoopedBurningSoundComponent->SetupAttachment(MeshComponent);
	LoopedBurningSoundComponent->bAutoActivate = false;
}

float ACurseExplosiveBarrel::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0)
	{
		// Start burning and explode after BurningDuration.
		if (!bIsBurning)
		{
			bIsBurning = true;

			LoopedBurningEffectComponent->ActivateSystem();
			LoopedBurningSoundComponent->Activate();

			GetWorldTimerManager().SetTimer(BurningTimerHandle, this, &ACurseExplosiveBarrel::Explode, BurningDuration, false);
		}
		// Explode immediately, invalidating explosion timer.
		else
		{
			if (BurningTimerHandle.IsValid()) BurningTimerHandle.Invalidate();
			Explode();
		}
	}

	return ActualDamage;
}

void ACurseExplosiveBarrel::Explode()
{
	ExplosionForceComponent->FireImpulse();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, LoopedBurningEffectComponent->GetComponentLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, LoopedBurningSoundComponent->GetComponentLocation());

	LoopedBurningEffectComponent->Deactivate();
	LoopedBurningSoundComponent->Deactivate();
	bIsBurning = false;

	// Destroy();
	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetHiddenInGame(true);
	SetLifeSpan(1.f);
}
