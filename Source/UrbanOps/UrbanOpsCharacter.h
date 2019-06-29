// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UrbanOpsEnumTypes.h"
#include "GameFramework/Character.h"
#include "UrbanOpsCharacter.generated.h"

UCLASS()
class URBANOPS_API AUrbanOpsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	// Category - Current Status 
	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Current Status")
	uint8 bIsDead : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Details", meta = (AllowPrivateAccess = "true"))
	ECharacterType CharacterType;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 ImpactDamage;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 MagicDamage;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 ImpactResistance;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 MagicResistance;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int MaximalHealth;

	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int CurrentHealth;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 MaximalStamina;

	/**  */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 CurrentStamina;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 Shield;

	/**  */
	UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	uint8 HealthRegeneration;

protected: // Override functions

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: // Override functions

	// Called every frame
	virtual void Tick(float DeltaTime) override;


public: /** Getters */

	/** Return percentage of current health */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetHealthPercentage()				{ return float(float(CurrentHealth) / float(MaximalHealth)); }

	/** Return percentage of current stamina */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStaminaPercentage()			{ return float(float(CurrentStamina) / float(MaximalStamina)); }

public:

	bool ApplyDamage(uint8 value);

	void Respawn();

	void Die_FromServerOnServerOnly();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Die();
	void Multicast_Die_Implementation();
	
public:

	FORCEINLINE bool IsDead() const						{ return this->bIsDead; }
	ECharacterType GetCharacterType() const				{ return CharacterType; }

public:
	// Sets default values for this character's properties
	AUrbanOpsCharacter();
};
