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

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<USoundBase> TeleportSound;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportEffectTime = 0.2f;

public:
	ACurseProjectileTeleport();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimeExpired();
	void TeleportInstigator(const FTransform& Location);
	void OnTeleportFinished();

	FTransform TeleportLocation;
	FTimerHandle TeleportTimerHandle;
};
