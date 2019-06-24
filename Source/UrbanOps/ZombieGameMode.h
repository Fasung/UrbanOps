// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/GameMode.h"
#include "ZombieGameMode.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API AZombieGameMode : public AGameMode
{
	GENERATED_BODY()
	
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "GameModeType", meta = (AllowPrivateAccess = "true"))
	EGameMode GameModeType;


public:

	AZombieGameMode();
};
