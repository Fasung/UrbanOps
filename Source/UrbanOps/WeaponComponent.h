// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class URBANOPS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	/** Store the off set of the arms for current weapon, use to adjust animations */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	FVector LeftHandOffSet;

	/** Store the IDs of selected weapon for each slot, there are 6 slots available */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	TArray<EWeaponID> SelectedWeapons;

	/** Store the id of last selected weapon slot */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	EWeaponSlot SelectedWeaponFromSlot;

	/** Store the ID of selected weapon type, could be pistol, rifle, launcher, etc.. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	EWeaponType SelectedWeaponTypeID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	EWeaponID SelectedWeaponID;

	/** Sound to play each time we fire */
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FireSound;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	/** Return the selected weapon type ID*/
	static EWeaponType GetSelectedWeaponTypeID(EWeaponID index);

	static FVector GetLeftHandOffSet(EWeaponID index);

public: /** Getters */

	FORCEINLINE TSubclassOf<class AProjectile> GetProjectileClass()		const { return ProjectileClass; }


	FORCEINLINE EWeaponID GetWeaponIDInSlotOne()		const	{ return SelectedWeapons[0]; }
	FORCEINLINE EWeaponID GetWeaponIDInSlotTwo()		const	{ return SelectedWeapons[1]; }
	FORCEINLINE EWeaponID GetWeaponIDInSlotThree()		const	{ return SelectedWeapons[2]; }
	FORCEINLINE EWeaponID GetWeaponIDInSlotFour()		const	{ return SelectedWeapons[3]; }
	FORCEINLINE EWeaponID GetWeaponIDInSlotFive()		const	{ return SelectedWeapons[4]; }
	FORCEINLINE EWeaponID GetWeaponIDInSlotSix()		const	{ return SelectedWeapons[5]; }

	FORCEINLINE EWeaponType GetSelectedWeaponTypeID()	const	{ return SelectedWeaponTypeID; }
	FORCEINLINE class USoundBase * GetFireSound()		const	{ return FireSound; }

	
public:

	/** Will swap weapons with weapon in selected weapon slot, if the weapon slot does not containt any weapon*/
	void SwapWeapons(const EWeaponSlot selectWeaponFromSlot);


public: /** Networking functions */
		
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotOne();
	void ServerRun_ChooseWeaponFromSlotOne_Implementation();
	bool ServerRun_ChooseWeaponFromSlotOne_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotTwo();
	void ServerRun_ChooseWeaponFromSlotTwo_Implementation();
	bool ServerRun_ChooseWeaponFromSlotTwo_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotThree();
	void ServerRun_ChooseWeaponFromSlotThree_Implementation();
	bool ServerRun_ChooseWeaponFromSlotThree_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotFour();
	void ServerRun_ChooseWeaponFromSlotFour_Implementation();
	bool ServerRun_ChooseWeaponFromSlotFour_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotFive();
	void ServerRun_ChooseWeaponFromSlotFive_Implementation();
	bool ServerRun_ChooseWeaponFromSlotFive_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_ChooseWeaponFromSlotSix();
	void ServerRun_ChooseWeaponFromSlotSix_Implementation();
	bool ServerRun_ChooseWeaponFromSlotSix_Validate();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ChooseSelectedWeaponSinglePar(EWeaponID newSelectedWeaponID);
	void Multicast_ChooseSelectedWeaponSinglePar_Implementation(EWeaponID newSelectedWeaponID);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ChooseSelectedWeaponDoublePar(EWeaponType newSelectedWeaponTypeID, EWeaponID newSelectedWeaponID);
	void Multicast_ChooseSelectedWeaponDoublePar_Implementation(EWeaponType newSelectedWeaponTypeID, EWeaponID newSelectedWeaponID);

public:
	// Sets default values for this component's properties
	UWeaponComponent();
		
};
