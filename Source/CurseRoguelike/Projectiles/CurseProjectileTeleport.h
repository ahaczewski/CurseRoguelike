// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "CurseProjectile.h"

#include "CurseProjectileTeleport.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class CURSEROGUELIKE_API ACurseProjectileTeleport : public ACurseProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<UNiagaraSystem> TeleportEffect;

public:
	ACurseProjectileTeleport();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void TeleportInstigator(const FTransform& Location);
};
