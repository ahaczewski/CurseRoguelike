// Copyright 2026 Andrzej Haczewski.

#include "CurseItemChest.h"

#include "CurseCollision.h"

ACurseItemChest::ACurseItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComponent->SetCollisionProfileName(Curse::Collision::InteractionProfile);
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	LidMeshComponent->SetGenerateOverlapEvents(false);
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ACurseItemChest::Interact()
{
	SetActorTickEnabled(true);
}

void ACurseItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentLidPitch = FMath::FInterpConstantTo(CurrentLidPitch, LidRotationTarget, DeltaTime, LidRotationSpeed);
	
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentLidPitch, 0, 0));
	
	if (FMath::IsNearlyEqual(CurrentLidPitch, LidRotationTarget))
	{
		SetActorTickEnabled(false);
	}
}
