// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

#include "CurseCollision.h"

ACurseProjectile::ACurseProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComponent->SetCollisionProfileName(Curse::Collision::ProjectileProfile);
	CollisionComponent->InitSphereRadius(16.f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	LoopedEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedEffectComp"));
	LoopedEffectComponent->SetupAttachment(CollisionComponent);

	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComponent->SetupAttachment(CollisionComponent);
}
