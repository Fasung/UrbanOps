// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateZombie.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API AGameStateZombie : public AGameState
{
	GENERATED_BODY()

	uint8 CurrentWeave;

	uint8 ZombiesLeft;


public:

	AGameStateZombie();
};
