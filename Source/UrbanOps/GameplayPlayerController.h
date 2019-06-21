// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "UnrealNetwork.h"
#include "GameplayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	UPROPERTY()
	class APlayerCharacter* PtrCharacter;

	/** Timer is used to detect double tapping on the W button */
	UPROPERTY()
	FTimerHandle timer;


	/**  */
	UPROPERTY()
	uint32 bIsSprintButtonPressedOnce : 1;

	/**  */
	UPROPERTY()
	uint32 bIsSprintButtonPressedTwice : 1;

private:

	void Turn(float scrollValue);
	void LookUp(float moveValue);

	void OnJumpBegin();
	void OnJumpFinish();

	void OnCrouchBegin();
	void OnCrouchExit();

	void OnMoveForwardPressed();
	void OnMoveForwardReleased();

	void OnFirePressed();
	void OnFireReleased();

	// Used for detecting if player wants to sprint or not
	void ResetMoveForwardInput();


	void OnChooseWeaponFromSlotOne();
	void OnChooseWeaponFromSlotTwo();
	void OnChooseWeaponFromSlotThree();
	void OnChooseWeaponFromSlotFour();
	void OnChooseWeaponFromSlotFive();
	void OnChooseWeaponFromSlotSix();

private:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


public: /** Constructors */
	AGameplayPlayerController();
};

