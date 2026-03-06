// Copyright 2026 Andrzej Haczewski.

#include "CurseCharacter.h"

// Sets default values
ACurseCharacter::ACurseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACurseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACurseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

