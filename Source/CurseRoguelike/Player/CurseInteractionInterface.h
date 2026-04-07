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
	UFUNCTION(BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation() {}
};
