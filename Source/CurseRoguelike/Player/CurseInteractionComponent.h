// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "CurseInteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CURSEROGUELIKE_API UCurseInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionRadius = 450.f;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

public:
	UCurseInteractionComponent();

	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<APlayerController> OwningPlayer;

private:
	const FOverlapResult* FindBestInteractable(const TArray<FOverlapResult>& Overlaps, const FVector& Origin, const FVector& LookDirection) const;
};
