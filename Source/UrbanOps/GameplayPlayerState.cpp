// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerState.h"
#include "WeaponComponent.h"
#include "Engine.h"
#include "UnrealNetwork.h"

AGameplayPlayerState::AGameplayPlayerState()
{
}


void AGameplayPlayerState::AddjustKills()
{
	Kills++;
}

void AGameplayPlayerState::AddjustDeads()
{
	Deads++;
}

void AGameplayPlayerState::AddjustAssists()
{
	Assists++;
}



void AGameplayPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameplayPlayerState, Kills);
	DOREPLIFETIME(AGameplayPlayerState, Deads);
	DOREPLIFETIME(AGameplayPlayerState, Assists);

}