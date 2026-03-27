// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "CurseInteractionInterface.generated.h"

UINTERFACE()
class UCurseInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CURSEROGUELIKE_API ICurseInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void Interact() PURE_VIRTUAL(ICurseInteractionInterface::Interact, )
};
