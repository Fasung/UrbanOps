// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	void Turn(float scrollValue);
	void LookUp(float moveValue);

private:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public: /** Constructors */
	AGameplayPlayerController();
};

