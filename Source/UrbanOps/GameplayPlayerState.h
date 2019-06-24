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

	/** Store the ID of selected class, can be Engineer, Medic, Assault or Sniper */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	EClass ClassID;

	/** Store the ID of selected weapon */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	ETeam TeamID;

	/** Store the ID of selected weapon */
	UPROPERTY(BlueprintReadOnly, Category = "CustomDetails", meta = (AllowPrivateAccess = "true"))
	uint8 Health;


public:

	FORCEINLINE bool DecreaseHealth(uint8 value);

public:
	
	AGameplayPlayerState();
};
