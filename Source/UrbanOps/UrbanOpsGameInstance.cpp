// Fill out your copyright notice in the Description page of Project Settings.


#include "UrbanOpsGameInstance.h"

FEngineerWeapons::FEngineerWeapons()
{
	WeaponSlotOne.Add(EWeaponID::HAND_POUNCH);
	WeaponSlotOne.Add(EWeaponID::MACHETE);

	WeaponSlotTwo.Add(EWeaponID::GLOCK17);
	WeaponSlotTwo.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotTwo.Add(EWeaponID::MP5);
	WeaponSlotTwo.Add(EWeaponID::REVOLVER);

	WeaponSlotThree.Add(EWeaponID::RPG);
	WeaponSlotThree.Add(EWeaponID::STINGER);

	WeaponSlotFour.Add(EWeaponID::AMMO_BOX);
	WeaponSlotFour.Add(EWeaponID::SPANNER);

	WeaponSlotFive.Add(EWeaponID::AMMO_BOX);
	WeaponSlotFive.Add(EWeaponID::GRENADE);
	WeaponSlotFive.Add(EWeaponID::SPANNER);

	WeaponSlotSix.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotSix.Add(EWeaponID::GLOCK17);
	WeaponSlotSix.Add(EWeaponID::GRENADE);
	WeaponSlotSix.Add(EWeaponID::MACHINE_GUN);
	WeaponSlotSix.Add(EWeaponID::MINIGUN);
	WeaponSlotSix.Add(EWeaponID::MP5);
	WeaponSlotSix.Add(EWeaponID::P60);
	WeaponSlotSix.Add(EWeaponID::REVOLVER);
	WeaponSlotSix.Add(EWeaponID::RPG);
	WeaponSlotSix.Add(EWeaponID::STINGER);
}

FMedicWeapons::FMedicWeapons()
{
	WeaponSlotOne.Add(EWeaponID::HAND_POUNCH);
	WeaponSlotOne.Add(EWeaponID::MACHETE);

	WeaponSlotTwo.Add(EWeaponID::GLOCK17);
	WeaponSlotTwo.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotTwo.Add(EWeaponID::MP5);
	WeaponSlotTwo.Add(EWeaponID::REVOLVER);

	WeaponSlotThree.Add(EWeaponID::M16);
	WeaponSlotThree.Add(EWeaponID::P60);

	WeaponSlotFour.Add(EWeaponID::MEDIC_BOX);

	WeaponSlotFive.Add(EWeaponID::GRENADE);

	WeaponSlotSix.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotSix.Add(EWeaponID::GLOCK17);
	WeaponSlotSix.Add(EWeaponID::GRENADE);
	WeaponSlotSix.Add(EWeaponID::M16);
	WeaponSlotSix.Add(EWeaponID::MP5);
	WeaponSlotSix.Add(EWeaponID::P60);
	WeaponSlotSix.Add(EWeaponID::REVOLVER);
}

FAssaultWeapons::FAssaultWeapons()
{
	WeaponSlotOne.Add(EWeaponID::HAND_POUNCH);
	WeaponSlotOne.Add(EWeaponID::MACHETE);

	WeaponSlotTwo.Add(EWeaponID::GLOCK17);
	WeaponSlotTwo.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotTwo.Add(EWeaponID::MP5);
	WeaponSlotTwo.Add(EWeaponID::REVOLVER);

	WeaponSlotThree.Add(EWeaponID::AK47);
	WeaponSlotThree.Add(EWeaponID::M16);
	WeaponSlotThree.Add(EWeaponID::SCAR);

	WeaponSlotFour.Add(EWeaponID::GRENADE);

	WeaponSlotSix.Add(EWeaponID::AK47);
	WeaponSlotSix.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotSix.Add(EWeaponID::GLOCK17);
	WeaponSlotSix.Add(EWeaponID::GRENADE);
	WeaponSlotSix.Add(EWeaponID::M16);
	WeaponSlotSix.Add(EWeaponID::MACHINE_GUN);
	WeaponSlotSix.Add(EWeaponID::MINIGUN);
	WeaponSlotSix.Add(EWeaponID::MP5);
	WeaponSlotSix.Add(EWeaponID::P60);
	WeaponSlotSix.Add(EWeaponID::REVOLVER);
	WeaponSlotSix.Add(EWeaponID::SCAR);
}

FSniperWeapons::FSniperWeapons()
{
	WeaponSlotOne.Add(EWeaponID::HAND_POUNCH);
	WeaponSlotOne.Add(EWeaponID::MACHETE);

	WeaponSlotTwo.Add(EWeaponID::GLOCK17);
	WeaponSlotTwo.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotTwo.Add(EWeaponID::MP5);
	WeaponSlotTwo.Add(EWeaponID::REVOLVER);

	WeaponSlotThree.Add(EWeaponID::L96);
	WeaponSlotThree.Add(EWeaponID::R8);

	WeaponSlotFour.Add(EWeaponID::GRENADE);

	WeaponSlotSix.Add(EWeaponID::DESERT_EAGLE);
	WeaponSlotSix.Add(EWeaponID::GLOCK17);
	WeaponSlotSix.Add(EWeaponID::GRENADE);
	WeaponSlotSix.Add(EWeaponID::MP5);
}

UUrbanOpsGameInstance::UUrbanOpsGameInstance()
{
	SelectedWeaponsEngineer.Add(EWeaponID::HAND_POUNCH);
	SelectedWeaponsEngineer.Add(EWeaponID::GLOCK17);
	SelectedWeaponsEngineer.Add(EWeaponID::RPG);
	SelectedWeaponsEngineer.Add(EWeaponID::SPANNER);
	SelectedWeaponsEngineer.Add(EWeaponID::AMMO_BOX);
	SelectedWeaponsEngineer.Add(EWeaponID::NO_WEAPON);

	SelectedWeaponsMedic.Add(EWeaponID::HAND_POUNCH);
	SelectedWeaponsMedic.Add(EWeaponID::GLOCK17);
	SelectedWeaponsMedic.Add(EWeaponID::M16);
	SelectedWeaponsMedic.Add(EWeaponID::GRENADE);
	SelectedWeaponsMedic.Add(EWeaponID::MEDIC_BOX);
	SelectedWeaponsMedic.Add(EWeaponID::NO_WEAPON);

	SelectedWeaponsAssault.Add(EWeaponID::MACHETE);
	SelectedWeaponsAssault.Add(EWeaponID::DESERT_EAGLE);
	SelectedWeaponsAssault.Add(EWeaponID::SCAR);
	SelectedWeaponsAssault.Add(EWeaponID::GRENADE);
	SelectedWeaponsAssault.Add(EWeaponID::NO_WEAPON);
	SelectedWeaponsAssault.Add(EWeaponID::MACHINE_GUN);

	SelectedWeaponsSniper.Add(EWeaponID::HAND_POUNCH);
	SelectedWeaponsSniper.Add(EWeaponID::MP5);
	SelectedWeaponsSniper.Add(EWeaponID::R8);
	SelectedWeaponsSniper.Add(EWeaponID::GRENADE);
	SelectedWeaponsSniper.Add(EWeaponID::NO_WEAPON);
	SelectedWeaponsSniper.Add(EWeaponID::DESERT_EAGLE);

	uint8 weaponsCount = (uint8)EWeaponID::WEAPONS_COUNT;

	for (uint8 i = 0; i < weaponsCount; i++)
	{
		OwnedWeapons.Add(true);
	}
}