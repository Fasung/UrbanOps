// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/PlayerState.h"
#include "GameplayPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class URBANOPS_API AGameplayPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	/** Store the ID of selected skin */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	ECharacterSkins SelectedSkinID;

	/** Store the ID of selected class, can be Engineer, Medic, Assault or Sniper */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	EClass SelectedClassID;

	/** Store the ID of selected weapon */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	ETeam SelectedTeamID;

	/** Store the ID of selected weapon type, could be pistol, rifle, launcher, etc.. */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	EWeaponType SelectedWeaponTypeID;

	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	/** Store the ID of selected weapon */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	EWeaponID SelectedWeaponID;

public:
	
	EWeaponID GetSelectedWeaponID()		const { return this->SelectedWeaponID; }

public:


	void SetSelectedWeapon(const class UWeaponComponent * ptrWeaponComponent, const EWeaponSlot selectWeaponFromSlot);


};
