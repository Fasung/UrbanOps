// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerController.h"
#include "PlayerCharacter.h"
#include "WeaponComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"



// MAYBE DELETE THIS
#include "Engine.h"


//#define MAXIMAL_WALK_SPEED 250
//#define MAXIMAL_RUN_SPEED 400

AGameplayPlayerController::AGameplayPlayerController()	: 
	bIsSprintButtonPressedOnce(false),
	bIsSprintButtonPressedTwice(false)
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



	if (PtrCharacter != NULL)
	{
		// Used for movement calculation
		FRotator newRotator;
		newRotator.Yaw = GetPawn()->GetControlRotation().Yaw;
		
		// Move character
		PtrCharacter->AddMovementInput(UKismetMathLibrary::GetRightVector(newRotator), -InputComponent->GetAxisKeyValue(EKeys::A) + InputComponent->GetAxisKeyValue(EKeys::D));
		PtrCharacter->AddMovementInput(UKismetMathLibrary::GetForwardVector(newRotator), InputComponent->GetAxisKeyValue(EKeys::W) + (-InputComponent->GetAxisKeyValue(EKeys::S)));
	}
}


void AGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PtrCharacter = Cast<APlayerCharacter>(GetPawn());
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

	InputComponent->BindKey(EKeys::W, IE_Pressed, this, &AGameplayPlayerController::OnMoveForwardPressed);
	InputComponent->BindKey(EKeys::W, IE_Released, this, &AGameplayPlayerController::OnMoveForwardReleased);

	InputComponent->BindKey(EKeys::LeftControl, IE_Pressed, this, &AGameplayPlayerController::OnCrouchBegin);
	InputComponent->BindKey(EKeys::LeftControl, IE_Released, this, &AGameplayPlayerController::OnCrouchExit);

	InputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AGameplayPlayerController::OnJumpBegin);
	InputComponent->BindKey(EKeys::SpaceBar, IE_Released, this, &AGameplayPlayerController::OnJumpFinish);

	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AGameplayPlayerController::OnFirePressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AGameplayPlayerController::OnFireReleased);

	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotOne);
	InputComponent->BindKey(EKeys::Two, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotTwo);
	InputComponent->BindKey(EKeys::Three, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotThree);
	InputComponent->BindKey(EKeys::Four, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotFour);
	InputComponent->BindKey(EKeys::Five, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotFive);
	InputComponent->BindKey(EKeys::Six, IE_Pressed, this, &AGameplayPlayerController::OnChooseWeaponFromSlotSix);




	//InputComponent->BindKey(EKeys::LeftShift, IE_Pressed, this, &AGameplayPlayerController::OnSprintBegin);
	//InputComponent->BindKey(EKeys::LeftShift, IE_Released, this, &AGameplayPlayerController::OnSprintFinish);

}


void AGameplayPlayerController::ResetMoveForwardInput()
{
	bIsSprintButtonPressedOnce = false;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ResetMoveForwardInput Called!"));

}

void AGameplayPlayerController::OnMoveForwardPressed()
{
	if (!bIsSprintButtonPressedOnce)
	{
		bIsSprintButtonPressedOnce = true;
	}
	else if (bIsSprintButtonPressedOnce)
	{
		bIsSprintButtonPressedTwice = true;
		PtrCharacter->ServerRun_OnSprintBegin();
		PtrCharacter->GetCharacterMovement()->MaxWalkSpeed = PtrCharacter->MAXIMAL_RUN_SPEED;
	}
}

void AGameplayPlayerController::OnMoveForwardReleased()
{
	if (!bIsSprintButtonPressedTwice) GetWorld()->GetTimerManager().SetTimer(this->timer, this, &AGameplayPlayerController::ResetMoveForwardInput, 0.3f, false);

	if (bIsSprintButtonPressedTwice)
	{
		PtrCharacter->ServerRun_OnSprintFinish();
		PtrCharacter->GetCharacterMovement()->MaxWalkSpeed = PtrCharacter->MAXIMAL_WALK_SPEED;
		bIsSprintButtonPressedTwice = false;
		bIsSprintButtonPressedOnce = false;
	}
}

void AGameplayPlayerController::OnJumpBegin()
{
	PtrCharacter->ServerRun_OnJumpBegin();
}

void AGameplayPlayerController::OnJumpFinish()
{
	PtrCharacter->ServerRun_OnJumpFinish();
}


void AGameplayPlayerController::OnCrouchBegin()
{
	PtrCharacter->ServerRun_OnCrounchBegin();
}

void AGameplayPlayerController::OnCrouchExit()
{
	PtrCharacter->ServerRun_OnCrounchFinish();
}

void AGameplayPlayerController::Turn(float value)
{
	if (PtrCharacter != NULL)
	{
		AddYawInput(value);
	}
}


void AGameplayPlayerController::LookUp(float value)
{
	if (PtrCharacter != NULL)
	{
		AddPitchInput(value);

		if (Role == ROLE_Authority)
		{
			PtrCharacter->PitchReplicated = UKismetMathLibrary::ClampAngle(PtrCharacter->GetControlRotation().Pitch, -90.f, 90.0f);
		}
		else 
		{
			PtrCharacter->ServerRun_AddjustPitch();
			PtrCharacter->PitchNotReplicated = UKismetMathLibrary::ClampAngle(PtrCharacter->GetControlRotation().Pitch, -90.f, 90.0f);
		}
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotOne()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotOne Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_ONE);
}

void AGameplayPlayerController::OnChooseWeaponFromSlotTwo()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotTwo Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_TWO);
}

void AGameplayPlayerController::OnChooseWeaponFromSlotThree()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotThree Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_THREE);
}

void AGameplayPlayerController::OnChooseWeaponFromSlotFour()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotFour Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_FOUR);
}

void AGameplayPlayerController::OnChooseWeaponFromSlotFive()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotFive Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_FIVE);
}

void AGameplayPlayerController::OnChooseWeaponFromSlotSix()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotSix Called!"));
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_SIX);
}


void AGameplayPlayerController::OnFirePressed()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnFirePressed Called!"));
	PtrCharacter->ServerRun_OnFireBegin();// ->SwapWeapons(EWeaponSlot::SLOT_SIX);

}

void AGameplayPlayerController::OnFireReleased()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnFireReleased Called!"));
	//PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_SIX);

}