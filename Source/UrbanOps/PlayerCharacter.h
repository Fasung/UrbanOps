// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class URBANOPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	// Store the ID of selected class, can be Engineer, Medic, Assault or Sniper
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Details", meta = (AllowPrivateAccess = "true"))
	EClass SelectedClass;

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MeshNoHead;
	
	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * CameraComponent;

	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Details", meta = (AllowPrivateAccess = "true"))
	ECharacterSkins SelectedSkin;

public:


	static const uint16 MAXIMAL_CROUNCH_SPEED = 225;
	static const uint16 MAXIMAL_WALK_SPEED = 385;
	static const uint16 MAXIMAL_RUN_SPEED = 610;

	// Category - Current Status 

	/**  */
	//UPROPERTY(Replicated, BlueprintReadOnly, Category = "Current Status")
	//uint32 bIsDeadReplicated : 1;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Current Status")
	uint32 bIsJumpingReplicated : 1;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Current Status")
	uint32 bIsSprintingReplicated : 1;



	// Category - Camera 
	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Camera")
	float PitchReplicated;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	float PitchNotReplicated;
	

public:

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	//virtual void Tick(float DeltaTime) override;
	


public:
	// Sets default values for this character's properties
	APlayerCharacter();

};
