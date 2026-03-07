// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileMagic.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
	
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComponent->SetupAttachment(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	
	DamageType = UDamageType::StaticClass();
}

void ACurseProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACurseProjectileMagic::OnHit);
	CollisionComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ACurseProjectileMagic::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, GetActorRotation().Vector(), Hit, GetInstigatorController(), this, DamageType);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());	

	Destroy();
}
