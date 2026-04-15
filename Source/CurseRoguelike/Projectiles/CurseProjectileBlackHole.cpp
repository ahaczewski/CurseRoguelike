// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

#include "CurseCollision.h"

ACurseProjectileBlackHole::ACurseProjectileBlackHole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(CollisionComponent);
	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->ForceStrength = -300000.f;
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->Falloff = RIF_Linear;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Vehicle));

	CollisionComponent->SetCollisionProfileName(Curse::Collision::OverlapPhysicsBodyProfile);
	CollisionComponent->SetSphereRadius(32.f);

	ProjectileMovementComponent->InitialSpeed = 500.f;

	InitialLifeSpan = 5.f;
}

void ACurseProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACurseProjectileBlackHole::OnOverlapBegin);
}

void ACurseProjectileBlackHole::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}
