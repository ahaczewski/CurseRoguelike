// Copyright 2026 Andrzej Haczewski.

#include "CursePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "Projectiles/CurseProjectileMagic.h"

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
	PlayAnimMontage(PrimaryAttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(
		CastingEffect,
		GetMesh(),
		ProjectileSpawnSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true);

	UGameplayStatics::PlaySound2D(this, CastingSound);

	FTimerHandle AttackTimerHandle;
	auto AttackTimer = FTimerDelegate::CreateWeakLambda(
		this,
		[this]()
		{
			FVector SpawnLocation = GetMesh()->GetSocketLocation(ProjectileSpawnSocketName);
			FRotator SpawnRotation = GetControlRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			auto* Projectile = GetWorld()->SpawnActor<ACurseProjectileMagic>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (!IsValid(Projectile)) return;

			MoveIgnoreActorAdd(Projectile);
		});

	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimer, PrimaryAttackDelayTime, false);
}
