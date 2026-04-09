// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "CurseProjectile.h"

#include "CurseProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Abstract)
class CURSEROGUELIKE_API ACurseProjectileMagic : public ACurseProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float BaseDamage = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<USoundBase> ExplosionSound;

public:
	ACurseProjectileMagic();

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
