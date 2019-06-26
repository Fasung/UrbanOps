// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerState.h"
#include "WeaponComponent.h"
#include "Engine.h"

AGameplayPlayerState::AGameplayPlayerState()	:
	Health(10)
{
}


bool AGameplayPlayerState::DecreaseHealth(uint8 value)
{
	this->Health -= value;
	if (this->Health < 1 || this->Health > 10) return true;
	else return false;
}

