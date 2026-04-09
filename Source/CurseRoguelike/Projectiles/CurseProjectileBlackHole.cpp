// Copyright 2026 Andrzej Haczewski.

#include "CurseProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ACurseProjectileBlackHole::ACurseProjectileBlackHole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(CollisionComponent);
	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->ForceStrength = 1000000.f;
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->Falloff = RIF_Linear;

	// TODO: set correct collision profile for collision component: overlap physical bodies / all dynamic, ignore pawn
	// TODO: set correct channel/trace/object type for force component

	InitialLifeSpan = 5.f;
}

void ACurseProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// TODO: Add overlap handler to destroy actors pulled in by the black hole
}
