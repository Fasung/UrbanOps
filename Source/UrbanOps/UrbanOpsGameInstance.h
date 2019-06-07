// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UrbanOpsEnumTypes.h"
#include "UrbanOpsGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FEngineerWeapons
{
	GENERATED_USTRUCT_BODY()
	
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotOne;
	
	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotTwo;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotThree;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFour;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFive;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotSix;

	//Constructor
	FEngineerWeapons();
};

USTRUCT(BlueprintType)
struct FMedicWeapons
{
	GENERATED_USTRUCT_BODY()
	
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotOne;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotTwo;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotThree;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFour;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFive;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotSix;
	
	//Constructor
	FMedicWeapons();
};

USTRUCT(BlueprintType)
struct FAssaultWeapons
{
	GENERATED_USTRUCT_BODY()
	
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotOne;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotTwo;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotThree;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFour;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFive;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotSix;
	
	//Constructor
	FAssaultWeapons();
};

USTRUCT(BlueprintType)
struct FSniperWeapons
{
	GENERATED_USTRUCT_BODY()
	
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotOne;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotTwo;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotThree;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFour;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotFive;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "WeaponSlots")
	TArray<EWeaponID> WeaponSlotSix;
	
	//Constructor
	FSniperWeapons();
};

USTRUCT(BlueprintType)
struct FClassesWeapons
{
	GENERATED_USTRUCT_BODY()

	/** Store all engineer weapons IDs for each slots */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (BlueprintProtected = "true"))
	FEngineerWeapons EngineerWeapons;

	/** Store all medic weapons IDs for each slots */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (BlueprintProtected = "true"))
	FMedicWeapons MedicWeapons;

	/** Store all assault weapons IDs for each slots */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (BlueprintProtected = "true"))
	FAssaultWeapons AssaultWeapons;

	/** Store all sniper weapons IDs for each slots */
	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (BlueprintProtected = "true"))
	FSniperWeapons SniperWeapons;

	//Constructor
	FClassesWeapons() {}
};

/**
 *
 */
UCLASS()
class URBANOPS_API UUrbanOpsGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	/** Store IDs of selected weapons for Engineer class. Index in array represent specific slot, Index 0 = slot1, Index 1 = slot2, etc..*/
	UPROPERTY(BlueprintReadWrite, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	TArray<EWeaponID> SelectedWeaponsEngineer;

	/** Store IDs of selected weapons for Medic class. Index in array represent specific slot, Index 0 = slot1, Index 1 = slot2, etc..*/
	UPROPERTY(BlueprintReadWrite, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	TArray<EWeaponID> SelectedWeaponsMedic;

	/** Store IDs of selected weapons for Medic class. Index in array represent specific slot, Index 0 = slot1, Index 1 = slot2, etc..*/
	UPROPERTY(BlueprintReadWrite, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	TArray<EWeaponID> SelectedWeaponsAssault;

	/** Store IDs of selected weapons for Medic class. Index in array represent specific slot, Index 0 = slot1, Index 1 = slot2, etc..*/
	UPROPERTY(BlueprintReadWrite, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	TArray<EWeaponID> SelectedWeaponsSniper;

	/** Store IDs of selected weapons for Medic class. Index in array represent specific slot, Index 0 = slot1, Index 1 = slot2, etc..*/
	UPROPERTY(BlueprintReadWrite, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	EClass SelectedClass;

	/** Check if player contain the weapon, to access specifics weapons by name, use enum EWeaponID, size of the array is equal to the
	count of weapons defined inside the enum EWeaponID */
	UPROPERTY(BlueprintReadOnly, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	TArray<bool> OwnedWeapons;

	/** Store informations about weapons */
	UPROPERTY(BlueprintReadOnly, Category = "ClassesAndWeapons", meta = (AllowPrivateAccess = "true"))
	FClassesWeapons ClassesWeapons;

public:

	FORCEINLINE const TArray<EWeaponID>& GetSelectedWeaponsEngineer()		const { return this->SelectedWeaponsEngineer; }
	FORCEINLINE const TArray<EWeaponID>& GetSelectedWeaponsMedic()			const { return this->SelectedWeaponsMedic; }
	FORCEINLINE const TArray<EWeaponID>& GetSelectedWeaponsAssault()		const { return this->SelectedWeaponsAssault; }
	FORCEINLINE const TArray<EWeaponID>& GetSelectedWeaponsSniper()			const { return this->SelectedWeaponsSniper; }
	FORCEINLINE const EClass GetSelectedClass()								const { return this->SelectedClass; }


public: // Constructor
	UUrbanOpsGameInstance();
};