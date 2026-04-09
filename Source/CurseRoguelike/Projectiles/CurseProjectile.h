// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "CurseProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class CURSEROGUELIKE_API ACurseProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:
	ACurseProjectile();
};
