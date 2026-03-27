// Copyright 2026 Andrzej Haczewski.

#include "CurseInteractionComponent.h"

#include "Engine/OverlapResult.h"

#include "CurseInteractionInterface.h"

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

	const APlayerController* PlayerController = OwningPlayer.Get();
	const APawn* Pawn = PlayerController->GetPawn();

	if (!IsValid(Pawn)) return;

	const FVector OriginVec = Pawn->GetActorLocation();
	TArray<FOverlapResult> Overlaps;

	GetWorld()->OverlapMultiByChannel(Overlaps, OriginVec, FQuat::Identity, TraceChannel, FCollisionShape::MakeSphere(InteractionRadius));

	const FOverlapResult* BestOverlap = FindBestInteractable(Overlaps, OriginVec, PlayerController->GetControlRotation().Vector());
	
	Interactable = BestOverlap ? BestOverlap->GetActor() : nullptr;

#if UE_ENABLE_DEBUG_DRAWING
	if (BestOverlap)
	{
		DrawDebugBox(GetWorld(), BestOverlap->GetActor()->GetActorLocation(), FVector(60.f), FColor::Emerald);
	}
	DrawDebugSphere(GetWorld(), OriginVec, InteractionRadius, 32, FColor::White);
#endif
}

const FOverlapResult*
UCurseInteractionComponent::FindBestInteractable(const TArray<FOverlapResult>& Overlaps, const FVector& Origin, const FVector& LookDirection) const
{
	const FOverlapResult* BestOverlap = nullptr;
	float MaxAngleCos = -2.f;

	for (const FOverlapResult& Overlap : Overlaps)
	{
		const FVector TargetVec = Overlap.GetActor()->GetActorLocation();
		FVector TargetDir = TargetVec - Origin;

		float AngleCos = TargetDir.CosineAngle2D(LookDirection);

		if (AngleCos > MaxAngleCos)
		{
			MaxAngleCos = AngleCos;
			BestOverlap = &Overlap;
		}

#if UE_ENABLE_DEBUG_DRAWING
		DrawDebugBox(GetWorld(), TargetVec, FVector(50.f), FColor::Orange);
		DrawDebugString(GetWorld(), FVector::UpVector * 100.f, FString::Printf(TEXT("%f"), AngleCos), Overlap.GetActor(), FColor::White, 0.f);
#endif
	}

	return BestOverlap;
}

void UCurseInteractionComponent::Interact() const
{
	if (Interactable.IsValid())
	{
		if (auto* InteractionInterface = Cast<ICurseInteractionInterface>(Interactable.Get()))
		{
			InteractionInterface->Interact();
		}
	}
}
