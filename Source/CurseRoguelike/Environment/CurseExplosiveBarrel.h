// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "CurseExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;
UCLASS(Abstract, Category = "Curse|Environment")
class CURSEROGUELIKE_API ACurseExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float BurningDuration = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> ExplosionForceComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedBurningEffectComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedBurningSoundComponent;

public:
	ACurseExplosiveBarrel();

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void Explode();
	
	bool bIsBurning = false;
	FTimerHandle BurningTimerHandle;
};
