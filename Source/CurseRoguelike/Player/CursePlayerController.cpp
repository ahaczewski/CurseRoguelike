// Copyright 2026 Andrzej Haczewski.

#include "CursePlayerController.h"

#include "EnhancedInputComponent.h"

#include "CurseInteractionComponent.h"

ACursePlayerController::ACursePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UCurseInteractionComponent>(TEXT("InteractionComp"));
}

void ACursePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ACursePlayerController::Interact);
}

void ACursePlayerController::Interact()
{
	InteractionComponent->Interact();
}
