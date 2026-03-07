// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

#include "CurseRoguelike/CurseCollision.h"

ACurseProjectileMagic::ACurseProjectileMagic()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComponent->SetCollisionProfileName(Curse::Collision::ProjectileProfile);
	CollisionComponent->InitSphereRadius(16.f);
	RootComponent = CollisionComponent;
	
	LoopedEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedEffectComp"));
	LoopedEffectComponent->SetupAttachment(CollisionComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
}
