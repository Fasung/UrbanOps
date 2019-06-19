// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerState.h"
#include "WeaponComponent.h"

void AGameplayPlayerState::SetSelectedWeapon(const UWeaponComponent* ptrWeaponComponent, const EWeaponSlot selectWeaponFromSlot)
{

	switch (selectWeaponFromSlot)
	{
	case EWeaponSlot::SLOT_ONE:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotOne();		
		break;
	case EWeaponSlot::SLOT_TWO:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotTwo();
		break;
	case EWeaponSlot::SLOT_THREE:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotThree();
		break;
	case EWeaponSlot::SLOT_FOUR:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotFour();
		break;
	case EWeaponSlot::SLOT_FIVE:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotFive();
		break;
	case EWeaponSlot::SLOT_SIX:
		this->SelectedWeaponID = ptrWeaponComponent->GetWeaponIDInSlotSix();
		break;
	}

	this->SelectedWeaponTypeID;
}