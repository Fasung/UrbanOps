// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UrbanOpsEnumTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EClass : uint8
{
	ENGINEER 	UMETA(DisplayName = "Engineer"),
	MEDIC 		UMETA(DisplayName = "Medic"),
	ASSAULT 	UMETA(DisplayName = "Assault"),
	SNIPER 		UMETA(DisplayName = "Sniper")
};

UENUM(BlueprintType)
enum class ECharacterSkins : uint8
{
	MALCOLN 	UMETA(DisplayName = "Malcoln"),
	SHAE 		UMETA(DisplayName = "Shae")
};

UENUM(BlueprintType)
enum class EWeaponID : uint8
{
	AK47 						UMETA(DisplayName = "AK47"),
	AMMO_BOX 					UMETA(DisplayName = "AmmoBox"),
	DESERT_EAGLE 				UMETA(DisplayName = "DesertEagle"),
	GLOCK17 					UMETA(DisplayName = "Glock17"),
	GRENADE 					UMETA(DisplayName = "Grenade"),
	HAND_POUNCH					UMETA(DisplayName = "HandPounch"),
	L96		 					UMETA(DisplayName = "L96"),
	M16		 					UMETA(DisplayName = "M16"),
	MACHETE 					UMETA(DisplayName = "Machete"),
	MACHINE_GUN					UMETA(DisplayName = "MachineGun"),
	MEDIC_BOX 					UMETA(DisplayName = "MedicBox"),
	MINIGUN 					UMETA(DisplayName = "Minigun"),
	MP5		 					UMETA(DisplayName = "MP5"),
	P60	 						UMETA(DisplayName = "P60"),
	R8 							UMETA(DisplayName = "R8"),
	REVOLVER 					UMETA(DisplayName = "Revolver"),
	RPG		 					UMETA(DisplayName = "RPG"),
	SCAR 						UMETA(DisplayName = "Scar"),
	SPANNER 					UMETA(DisplayName = "Spanner"),
	STINGER 					UMETA(DisplayName = "Stinger"),
	NO_WEAPON 					UMETA(DisplayName = "NoWeaponSelected"),
	WEAPONS_COUNT = NO_WEAPON
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	PISTOL			UMETA(DisplayName = "Pistol"),
	RIFLE			UMETA(DisplayName = "Rifle"),
	HANDS			UMETA(DisplayName = "Hands"),
};

UENUM(BlueprintType)
enum class ETeam : uint8
{
	TEAM_ONE			UMETA(DisplayName = "TeamOne"),
	TEAM_TWO			UMETA(DisplayName = "TeamTwo")
};

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	SLOT_ONE			UMETA(DisplayName = "SlotOne"),
	SLOT_TWO			UMETA(DisplayName = "SlotTwo"),
	SLOT_THREE			UMETA(DisplayName = "SlotThree"),
	SLOT_FOUR			UMETA(DisplayName = "SlotFour"),
	SLOT_FIVE			UMETA(DisplayName = "SlotFive"),
	SLOT_SIX			UMETA(DisplayName = "SlotSix"),
	NONE				UMETA(DisplayName = "TeamTwo")
};


UENUM(BlueprintType)
enum class EGameMode : uint8
{
	ZOMBIE_MODE			UMETA(DisplayName = "ZombieMode"),
	LOBBY_MODE			UMETA(DisplayName = "LobbyMode")
};