// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "CurseCharacter.generated.h"

class ACurseProjectileMagic;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Category = "Curse|Player")
class CURSEROGUELIKE_API ACurseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<ACurseProjectileMagic> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	FName ProjectileSpawnSocketName = "Muzzle_01";
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

public:
	ACurseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void Move(const FInputActionValue& ActionValue);
	void Look(const FInputActionInstance& ActionInstance);
	void PrimaryAttack();
};
