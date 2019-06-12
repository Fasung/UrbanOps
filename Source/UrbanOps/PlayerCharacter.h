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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details", meta = (AllowPrivateAccess = "true"))
	EClass SelectedClass;


	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * CameraComponent;

	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	// FIND THE RIGHT PLACE FOR THIS VARIABLE, MIGHT BE PlayerState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details", meta = (AllowPrivateAccess = "true"))
	ECharacterSkins SelectedSkin;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	//virtual void Tick(float DeltaTime) override;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

};
