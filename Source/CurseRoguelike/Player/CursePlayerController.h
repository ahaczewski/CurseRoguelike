// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "CursePlayerController.generated.h"

class UCurseInteractionComponent;

UCLASS()
class CURSEROGUELIKE_API ACursePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCurseInteractionComponent> InteractionComponent;
	
public:
	ACursePlayerController();
};
