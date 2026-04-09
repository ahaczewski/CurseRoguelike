// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

ACurseProjectileMagic::ACurseProjectileMagic()
{
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
