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
	ECharacterSkins SkinID;

	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	// DEPRICATED
	/** Store the ID of selected class, can be Engineer, Medic, Assault or Sniper */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	EClass ClassID;

	/** Store the ID of selected weapon */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	ETeam TeamID;

	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 Kills;

	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 Deads;

	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 Assists;

public:

	UFUNCTION()	void AddjustKills();
	UFUNCTION()	void AddjustDeads();
	UFUNCTION()	void AddjustAssists();

public:
	
	AGameplayPlayerState();
};
