// Copyright 2026 Andrzej Haczewski.

#include "CurseCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACurseCharacter::ACurseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACurseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACurseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACurseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ACurseCharacter::Move);	
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ACurseCharacter::Look);	
}

void ACurseCharacter::Move(const FInputActionValue& ActionValue)
{
	const auto InputVec = ActionValue.Get<FVector2D>();
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	
	AddMovementInput(ControlRot.Vector(), InputVec.X);
	AddMovementInput(ControlRot.RotateVector(FVector::RightVector), InputVec.Y);
}

void ACurseCharacter::Look(const FInputActionInstance& ActionInstance)
{
	const auto InputVec = ActionInstance.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(InputVec.Y);
	AddControllerYawInput(InputVec.X);
}
