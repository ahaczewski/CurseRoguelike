// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "CurseProjectile.h"

#include "CurseProjectileBlackHole.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class CURSEROGUELIKE_API ACurseProjectileBlackHole : public ACurseProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

public:
	ACurseProjectileBlackHole();

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
