// Copyright 2026 Andrzej Haczewski.

#include "CurseInteractionComponent.h"

UCurseInteractionComponent::UCurseInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UCurseInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	OwningPlayer = CastChecked<APlayerController>(GetOwner());
}

void UCurseInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (const APawn* Pawn = OwningPlayer.Get()->GetPawn(); IsValid(Pawn))
	{
		DrawDebugBox(GetWorld(), Pawn->GetActorLocation(), FVector(20.f), FColor::Orange);		
	}
}
