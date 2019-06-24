// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class URBANOPS_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameModeType", meta = (AllowPrivateAccess = "true"))
	EGameMode GameModeType;

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerInput")
	void ShowScoresTable();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerInput")
	void HideScoresTable();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerInput")
	void OpenCloseOptionsMenu();


public:

	AGameplayHUD();
};
