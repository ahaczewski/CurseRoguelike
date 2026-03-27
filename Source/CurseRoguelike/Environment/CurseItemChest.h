// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Player/CurseInteractionInterface.h"

#include "CurseItemChest.generated.h"

UCLASS(Abstract)
class CURSEROGUELIKE_API ACurseItemChest : public AActor, public ICurseInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Lid")
	float LidRotationSpeed = 60.f;

	UPROPERTY(EditDefaultsOnly, Category = "Lid")
	float LidRotationTarget = 120.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

public:
	ACurseItemChest();

	virtual void Interact() override;

	virtual void Tick(float DeltaTime) override;

private:
	float CurrentLidPitch = 0.f;
};
