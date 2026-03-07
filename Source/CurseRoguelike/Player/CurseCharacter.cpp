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
}

void ACurseCharacter::Move(const FInputActionValue& InValue)
{
	const auto InputVector = InValue.Get<FVector2D>();
	const auto MoveDirection = FVector(InputVector, 0.f);
	
	AddMovementInput(MoveDirection);
}
