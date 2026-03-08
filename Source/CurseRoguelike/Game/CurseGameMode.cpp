// Copyright 2026 Andrzej Haczewski.

#include "CurseGameMode.h"

#include "Player/CursePlayerController.h"

ACurseGameMode::ACurseGameMode()
{
	PlayerControllerClass = ACursePlayerController::StaticClass();
}
