// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "CursePlayerCharacter.generated.h"

class UNiagaraSystem;
class ACurseProjectile;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CURSEROGUELIKE_API ACursePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAttack")
	TSubclassOf<ACurseProjectile> PrimaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAttack")
	TObjectPtr<UAnimMontage> PrimaryAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAttack")
	float PrimaryAttackDelayTime = 0.2;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAttack")
	FName ProjectileSpawnSocketName = "Muzzle_01";

	UPROPERTY(EditDefaultsOnly, Category = "Ability|SecondaryAttack")
	TSubclassOf<ACurseProjectile> SecondaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|SecondaryAttack")
	TObjectPtr<UAnimMontage> SecondaryAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|SecondaryAttack")
	float SecondaryAttackDelayTime = 0.2;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|SecondaryAttack")
	FName SecondaryAttackSpawnSocketName = "Muzzle_01";

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAbility")
	TSubclassOf<ACurseProjectile> PrimaryAbilityProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAbility")
	TObjectPtr<UAnimMontage> PrimaryAbilityMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAbility")
	float PrimaryAbilityDelayTime = 0.2;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|PrimaryAbility")
	FName PrimaryAbilitySocketName = "Muzzle_01";

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TObjectPtr<USoundBase> CastingSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAbility;

public:
	ACursePlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& ActionValue);
	void Look(const FInputActionInstance& ActionInstance);
	void PrimaryAttack();
	void SecondaryAttack();
	void PrimaryAbility();

	void TriggerAbility(
		UAnimMontage* AbilityAnimMontage,
		UNiagaraSystem* AbilityEffect,
		USoundBase* AbilitySound,
		UClass* ProjectileClass,
		float DelayTime,
		FName SpawnSocketName);
};
