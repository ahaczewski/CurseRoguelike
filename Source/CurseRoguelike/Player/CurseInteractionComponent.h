// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "CurseInteractionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CURSEROGUELIKE_API UCurseInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCurseInteractionComponent();

	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<APlayerController> OwningPlayer;
};
