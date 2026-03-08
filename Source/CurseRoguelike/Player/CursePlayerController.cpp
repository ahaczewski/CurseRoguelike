// Copyright 2026 Andrzej Haczewski.

#include "CursePlayerController.h"

#include "CurseInteractionComponent.h"

ACursePlayerController::ACursePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UCurseInteractionComponent>(TEXT("InteractionComp"));
}
