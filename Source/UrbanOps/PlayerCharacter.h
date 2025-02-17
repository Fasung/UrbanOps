// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/Character.h"
#include "UrbanOpsCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class URBANOPS_API APlayerCharacter : public AUrbanOpsCharacter
{
	GENERATED_BODY()

private:
	
	/** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * CameraComponent;

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* WeaponComponent;

	/** The weapon skeletal mesh associated with this Character  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;


public:

	static const uint16 MAXIMAL_CROUNCH_SPEED = 215;
	static const uint16 MAXIMAL_CROUNCH_SPEED_BACKWARDS = 150;
	static const uint16 MAXIMAL_WALK_SPEED = 350;
	static const uint16 MAXIMAL_WALK_SPEED_BACKWARDS = 260;
	static const uint16 MAXIMAL_RUN_SPEED = 600;

	// Category - Current Status 
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "CurrentStatus")
	uint8 bIsJumpingReplicated : 1;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "CurrentStatus")
	uint8 bIsSprintingReplicated : 1;

	// Category - Camera 
	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Camera")
	float PitchReplicated;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	float PitchNotReplicated;
	
	/** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	//TSubclassOf<class AProjectile> ProjectileClass;

public:

	FORCEINLINE	class UWeaponComponent* GetWeaponComponent() const { return this->WeaponComponent; }

	FORCEINLINE	class USkeletalMeshComponent* GetWeaponMesh() const { return this->WeaponMesh; }


	/** Pick up the item*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void SwapWeaponMeshes(EWeaponID newSelectedWeaponID);

public: /**/

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_AddjustPitch();
	void ServerRun_AddjustPitch_Implementation();
	bool ServerRun_AddjustPitch_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnCrounchBegin();
	void ServerRun_OnCrounchBegin_Implementation();
	bool ServerRun_OnCrounchBegin_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnCrounchFinish();
	void ServerRun_OnCrounchFinish_Implementation();
	bool ServerRun_OnCrounchFinish_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnJumpBegin();
	void ServerRun_OnJumpBegin_Implementation();
	bool ServerRun_OnJumpBegin_Validate();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnSprintBegin();
	void Multicast_OnSprintBegin_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnSprintFinish();
	void Multicast_OnSprintFinish_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnJumpBegin();
	void Multicast_OnJumpBegin_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnCrounchBegin();
	void Multicast_OnCrounchBegin_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnCrounchFinish();
	void Multicast_OnCrounchFinish_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnJumpFinish();
	void ServerRun_OnJumpFinish_Implementation();
	bool ServerRun_OnJumpFinish_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnSprintBegin();
	void ServerRun_OnSprintBegin_Implementation();
	bool ServerRun_OnSprintBegin_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnSprintFinish();
	void ServerRun_OnSprintFinish_Implementation();
	bool ServerRun_OnSprintFinish_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRun_OnFireBegin(FVector testLocation, FRotator testRotation);
	void ServerRun_OnFireBegin_Implementation(FVector testLocation, FRotator testRotation);
	bool ServerRun_OnFireBegin_Validate(FVector testLocation, FRotator testRotation);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayFireAndWeaponEffect();
	void Multicast_PlayFireAndWeaponEffect_Implementation();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	//virtual void Tick(float DeltaTime) override;
	


public:
	// Sets default values for this character's properties
	APlayerCharacter();
};
