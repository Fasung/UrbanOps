// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"

ALobbyController::ALobbyController()
{
	bShowMouseCursor = true;
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
}