// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "PlayerCharacter.h"
#include "GameplayPlayerState.h"
#include "UnrealNetwork.h"

// MAYBE DELETE THIS
// MAYBE DELETE THIS
// MAYBE DELETE THIS

#include "Engine.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SelectedWeapons.Add(EWeaponID::GLOCK17);
	SelectedWeapons.Add(EWeaponID::SCAR);
	SelectedWeapons.Add(EWeaponID::MACHINE_GUN);
	SelectedWeapons.Add(EWeaponID::GLOCK17);
	SelectedWeapons.Add(EWeaponID::SCAR);
	SelectedWeapons.Add(EWeaponID::MACHINE_GUN);	// ...

	//Weapon = CreateDefaultSubobject<AWeapon>((TEXT("Weapon")));
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UWeaponComponent::SwapWeapons(const EWeaponSlot selectWeaponFromSlot)
{
	// If player does not press the same slot again, than choose different weapon
	if (SelectedWeaponFromSlot != selectWeaponFromSlot)
	{
		switch (selectWeaponFromSlot)
		{
		case EWeaponSlot::SLOT_ONE:	
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_ONE] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotOne();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_ONE;
			break;
		case EWeaponSlot::SLOT_TWO:
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_TWO] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotTwo();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_TWO;
			break;
		case EWeaponSlot::SLOT_THREE:
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_THREE] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotThree();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_THREE;
			break;
		case EWeaponSlot::SLOT_FOUR:
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_FOUR] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotFour();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_FOUR;
			break;
		case EWeaponSlot::SLOT_FIVE:
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_FIVE] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotFive();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_FIVE;
			break;
		case EWeaponSlot::SLOT_SIX:
			if (SelectedWeapons[(uint8)EWeaponSlot::SLOT_SIX] != EWeaponID::NO_WEAPON)
			{
				this->ServerRun_ChooseWeaponFromSlotSix();
			}
			this->SelectedWeaponFromSlot = EWeaponSlot::SLOT_SIX;
			break;
		}
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
////		 SERVER RUN			////////		 SERVER RUN			////		 SERVER RUN			////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotOne_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotOne();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotTwo_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotTwo();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotThree_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotThree();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotFour_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotFour();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotFive_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotFive();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

void UWeaponComponent::ServerRun_ChooseWeaponFromSlotSix_Implementation()
{
	bool tempBoolSendSingleParameter = true;
	this->SelectedWeaponID = GetWeaponIDInSlotSix();

	if (GetSelectedWeaponTypeID(SelectedWeaponID) != this->SelectedWeaponTypeID)
	{
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		this->SelectedWeaponTypeID = GetSelectedWeaponTypeID(SelectedWeaponID);
		tempBoolSendSingleParameter = false;
	}

	if (tempBoolSendSingleParameter) Multicast_ChooseSelectedWeaponSinglePar(this->SelectedWeaponID);
	else Multicast_ChooseSelectedWeaponDoublePar(this->SelectedWeaponTypeID, this->SelectedWeaponID);
}

bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotOne_Validate()			{ return true; }
bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotTwo_Validate()			{ return true; }
bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotThree_Validate()		{ return true; }
bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotFour_Validate()		{ return true; }
bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotFive_Validate()		{ return true; }
bool UWeaponComponent::ServerRun_ChooseWeaponFromSlotSix_Validate()			{ return true; }


/////////////////////////////////////////////////////////////////////////////////////////////////
////		 MULTI CAST		 ////////		 MULTI CAST		 ////////		 MULTI CAST		 ////
/////////////////////////////////////////////////////////////////////////////////////////////////

void UWeaponComponent::Multicast_ChooseSelectedWeaponSinglePar_Implementation(EWeaponID newSelectedWeaponID)
{
	APlayerCharacter* ptrCharacter = Cast<APlayerCharacter>(GetOwner());
	if (ptrCharacter)
	{
		this->SelectedWeaponID = newSelectedWeaponID;
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		ptrCharacter->SwapWeaponMeshes(newSelectedWeaponID);
	}
}

void UWeaponComponent::Multicast_ChooseSelectedWeaponDoublePar_Implementation(EWeaponType newSelectedWeaponTypeID, EWeaponID newSelectedWeaponID)
{
	APlayerCharacter* ptrCharacter = Cast<APlayerCharacter>(GetOwner());
	if (ptrCharacter)
	{
		this->SelectedWeaponTypeID = newSelectedWeaponTypeID;
		this->SelectedWeaponID = newSelectedWeaponID;
		this->LeftHandOffSet = GetLeftHandOffSet(SelectedWeaponID);
		ptrCharacter->SwapWeaponMeshes(newSelectedWeaponID);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////		 STATIC FUNCTIONS		 ////////		 STATIC FUNCTIONS		 ////////		 STATIC FUNCTIONS		 ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EWeaponType UWeaponComponent::GetSelectedWeaponTypeID(EWeaponID index)
{
	switch (index)
	{
	case EWeaponID::AK47:			return EWeaponType::RIFLE;		break;
		//case EWeaponID::AMMO_BOX:										break;
	case EWeaponID::DESERT_EAGLE:	return EWeaponType::PISTOL;		break;
	case EWeaponID::GLOCK17:		return EWeaponType::PISTOL;		break;
		//case EWeaponID::GRENADE:										break;
		//case EWeaponID::HAND_POUNCH:									break;
	case EWeaponID::L96:			return EWeaponType::RIFLE;		break;
	case EWeaponID::M16:			return EWeaponType::RIFLE;		break;
		//case EWeaponID::MACHETE:										break;
	case EWeaponID::MACHINE_GUN:	return EWeaponType::RIFLE;		break;
		//case EWeaponID::MEDIC_BOX:									break;
		//case EWeaponID::MINIGUN:										break;
	case EWeaponID::MP5:			return EWeaponType::RIFLE;		break;
	case EWeaponID::P60:			return EWeaponType::RIFLE;		break;
	case EWeaponID::R8:				return EWeaponType::RIFLE;		break;
	case EWeaponID::REVOLVER:		return EWeaponType::PISTOL;		break;
		//case EWeaponID::RPG:											break;
	case EWeaponID::SCAR:			return EWeaponType::RIFLE;		break;
		//case EWeaponID::SPANNER:										break;
		//case EWeaponID::STINGER:										break;
		//case EWeaponID::NO_WEAPON:									break;
	}

	// TODO CHANGE IT !!!
	// TODO CHANGE IT !!!
	// TODO CHANGE IT !!!
	// TODO CHANGE IT !!!

	return EWeaponType::RIFLE;
}

FVector UWeaponComponent::GetLeftHandOffSet(EWeaponID index)
{
	switch (index)
	{
	case EWeaponID::AK47:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::AMMO_BOX:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::DESERT_EAGLE:	return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::GLOCK17:		return FVector(0.0f, 13.0f, 0.0f);		break;
	case EWeaponID::GRENADE:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::HAND_POUNCH:	return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::L96:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::M16:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::MACHETE:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::MACHINE_GUN:	return FVector(-74.0f, 23.0f, 0.0f);	break;
	case EWeaponID::MEDIC_BOX:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::MINIGUN:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::MP5:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::P60:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::R8:				return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::REVOLVER:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::RPG:			return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::SCAR:			return FVector(-74.0f, 23.0f, 0.0f);	break;
	case EWeaponID::SPANNER:		return FVector(0.0f, 0.0f, 0.0f);		break;
	case EWeaponID::STINGER:		return FVector(0.0f, 0.0f, 0.0f);		break;
	}
	return FVector(0.0f, 0.0f, 0.0f);
}
