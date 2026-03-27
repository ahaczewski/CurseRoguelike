// Copyright 2026 Andrzej Haczewski.

#include "CurseItemChest.h"

ACurseItemChest::ACurseItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
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
