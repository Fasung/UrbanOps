// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "GameModeType", meta = (AllowPrivateAccess = "true"))
	EGameMode GameModeType;


public: // Deprecated function

	UFUNCTION(BlueprintPure, Category = "DEBUG")
	FString GetPathDebug();

public: // Constructor

	ALobbyGameMode();
};
