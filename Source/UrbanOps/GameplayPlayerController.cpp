// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerController.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine.h"

AGameplayPlayerController::AGameplayPlayerController()
{
	bShowMouseCursor = false;
	bEnableMouseOverEvents = false;
	bEnableClickEvents = false;
	DefaultMouseCursor = EMouseCursor::Default;
}


void AGameplayPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	/*
	if (GEngine)	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" W: %f S: %f A: %f D: %f CTRL: %f Shift: %f Space: %f"),
		InputComponent->GetAxisKeyValue(EKeys::W),
		InputComponent->GetAxisKeyValue(EKeys::S),
		InputComponent->GetAxisKeyValue(EKeys::A),
		InputComponent->GetAxisKeyValue(EKeys::D),
		InputComponent->GetAxisKeyValue(EKeys::LeftControl),
		InputComponent->GetAxisKeyValue(EKeys::LeftShift),
		InputComponent->GetAxisKeyValue(EKeys::SpaceBar)));
		*/

	APlayerCharacter * tempCharacter = Cast<APlayerCharacter>(GetPawn());


	if (tempCharacter != NULL)
	{
		// Used for movement calculation
		FRotator newRotator;
		newRotator.Yaw = GetPawn()->GetControlRotation().Yaw;
		
		// Move character
		tempCharacter->AddMovementInput(UKismetMathLibrary::GetRightVector(newRotator), -InputComponent->GetAxisKeyValue(EKeys::A) + InputComponent->GetAxisKeyValue(EKeys::D));
		tempCharacter->AddMovementInput(UKismetMathLibrary::GetForwardVector(newRotator), InputComponent->GetAxisKeyValue(EKeys::W) + (-InputComponent->GetAxisKeyValue(EKeys::S)));
	
		// Jump
		if (InputComponent->GetAxisKeyValue(EKeys::SpaceBar)) tempCharacter->Jump();

		// Crouch
		//if (InputComponent->GetAxisKeyValue(EKeys::LeftControl))
		//{
		//	if (!tempCharacter->bIsCrouched) tempCharacter->Crouch();
		//	else tempCharacter->UnCrouch();
		//}
	}
}


void AGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AGameplayPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Camera controllers actions, controled by mouse clicks and scrolls
	InputComponent->BindAxis("Turn", this, &AGameplayPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AGameplayPlayerController::LookUp);

	// Camera controllers actions, controled by mouse clicks and scrolls
	InputComponent->BindAxisKey(EKeys::W);
	InputComponent->BindAxisKey(EKeys::S);
	InputComponent->BindAxisKey(EKeys::A);
	InputComponent->BindAxisKey(EKeys::D);
	InputComponent->BindAxisKey(EKeys::LeftShift);
	InputComponent->BindAxisKey(EKeys::LeftControl);
	InputComponent->BindAxisKey(EKeys::SpaceBar);

}

void AGameplayPlayerController::Turn(float value)
{
	if (GetHUD() != NULL)
	AddYawInput(value);
}


void AGameplayPlayerController::LookUp(float value)
{
	if (GetHUD() != NULL)
	AddPitchInput(value);
}