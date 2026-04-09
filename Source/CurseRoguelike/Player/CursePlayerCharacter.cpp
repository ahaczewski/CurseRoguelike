// Copyright 2026 Andrzej Haczewski.

#include "CursePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "Projectiles/CurseProjectile.h"

ACursePlayerCharacter::ACursePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACursePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACursePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ACursePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ACursePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Started, this, &ACursePlayerCharacter::Jump);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Completed, this, &ACursePlayerCharacter::StopJumping);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ACursePlayerCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, &ACursePlayerCharacter::SecondaryAttack);
	EnhancedInput->BindAction(Input_PrimaryAbility, ETriggerEvent::Triggered, this, &ACursePlayerCharacter::PrimaryAbility);
}

void ACursePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACursePlayerCharacter::Move(const FInputActionValue& ActionValue)
{
	const auto InputVec = ActionValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;

	AddMovementInput(ControlRot.Vector(), InputVec.X);
	AddMovementInput(ControlRot.RotateVector(FVector::RightVector), InputVec.Y);
}

void ACursePlayerCharacter::Look(const FInputActionInstance& ActionInstance)
{
	const auto InputVec = ActionInstance.GetValue().Get<FVector2D>();

	AddControllerPitchInput(InputVec.Y);
	AddControllerYawInput(InputVec.X);
}

void ACursePlayerCharacter::PrimaryAttack()
{
	TriggerAbility(PrimaryAttackMontage, CastingEffect, CastingSound, PrimaryAttackProjectileClass, PrimaryAttackDelayTime, ProjectileSpawnSocketName);
}

void ACursePlayerCharacter::SecondaryAttack()
{
	TriggerAbility(SecondaryAttackMontage, CastingEffect, CastingSound, SecondaryAttackProjectileClass, SecondaryAttackDelayTime, SecondaryAttackSpawnSocketName);
}

void ACursePlayerCharacter::PrimaryAbility()
{
	TriggerAbility(PrimaryAbilityMontage, CastingEffect, CastingSound, PrimaryAbilityProjectileClass, PrimaryAbilityDelayTime, PrimaryAbilitySocketName);
}

void ACursePlayerCharacter::TriggerAbility(
	UAnimMontage* AbilityAnimMontage,
	UNiagaraSystem* AbilityEffect,
	USoundBase* AbilitySound,
	UClass* ProjectileClass,
	float DelayTime,
	FName SpawnSocketName)
{
	PlayAnimMontage(AbilityAnimMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(
		AbilityEffect,
		GetMesh(),
		ProjectileSpawnSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true);

	UGameplayStatics::PlaySound2D(this, AbilitySound);

	FTimerHandle AbilityTimerHandle;
	auto AbilityTimer = FTimerDelegate::CreateWeakLambda(
		this,
		[this, ProjectileClass, SpawnSocketName]()
		{
			FVector SpawnLocation = GetMesh()->GetSocketLocation(SpawnSocketName);
			FRotator SpawnRotation = GetControlRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			auto* Projectile = GetWorld()->SpawnActor<ACurseProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (!IsValid(Projectile)) return;

			MoveIgnoreActorAdd(Projectile);
		});

	GetWorldTimerManager().SetTimer(AbilityTimerHandle, AbilityTimer, DelayTime, false);
}
