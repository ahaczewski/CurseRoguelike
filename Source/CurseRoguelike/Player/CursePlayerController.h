// Copyright 2026 Andrzej Haczewski.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "CursePlayerController.generated.h"

class UInputAction;
class UCurseInteractionComponent;

UCLASS()
class CURSEROGUELIKE_API ACursePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCurseInteractionComponent> InteractionComponent;
	
public:
	ACursePlayerController();

protected:
	virtual void SetupInputComponent() override;
	
private:
	void Interact();
};
