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
	UPROPERTY(EditDefaultsOnly, Category = "Barrel")
	float BurningDuration = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Barrel")
	TObjectPtr<UNiagaraSystem> BurningEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Barrel")
	TObjectPtr<USoundBase> BurningSound;

	UPROPERTY(EditDefaultsOnly, Category = "Barrel")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Barrel")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	/**
	 * NOTE: The position of this component is used to spawn all effects and sounds. 
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> ExplosionForceComponent;

public:
	ACurseExplosiveBarrel();

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void Explode();
	
	bool bIsExploded = false;
	bool bIsBurning = false;
	FTimerHandle BurningTimerHandle;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> BurningEffectComponent;

	UPROPERTY()
	TObjectPtr<UAudioComponent> BurningSoundComponent;

};
