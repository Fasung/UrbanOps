// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayPlayerController.h"
#include "PlayerCharacter.h"
#include "GameplayHUD.h"
#include "WeaponComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"


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
		if (!PtrCharacter->bIsDead)
		{
			// Used for movement calculation
			FRotator newRotator;
			newRotator.Yaw = GetPawn()->GetControlRotation().Yaw;

			// Move character
			PtrCharacter->AddMovementInput(UKismetMathLibrary::GetRightVector(newRotator), -InputComponent->GetAxisKeyValue(EKeys::A) + InputComponent->GetAxisKeyValue(EKeys::D));
			PtrCharacter->AddMovementInput(UKismetMathLibrary::GetForwardVector(newRotator), InputComponent->GetAxisKeyValue(EKeys::W) + (-InputComponent->GetAxisKeyValue(EKeys::S)));
		}
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


	InputComponent->BindKey(EKeys::Tab, IE_Pressed, this, &AGameplayPlayerController::OnShowScoreTablePressed);
	InputComponent->BindKey(EKeys::Tab, IE_Released, this, &AGameplayPlayerController::OnShowScoreTableReleased);

	InputComponent->BindKey(EKeys::P, IE_Pressed, this, &AGameplayPlayerController::OnOpenCloseOptionMenuPressed);


	//InputComponent->BindKey(EKeys::LeftShift, IE_Pressed, this, &AGameplayPlayerController::OnSprintBegin);
	//InputComponent->BindKey(EKeys::LeftShift, IE_Released, this, &AGameplayPlayerController::OnSprintFinish);

}


void AGameplayPlayerController::ResetMoveForwardInput()
{
	bIsSprintButtonPressedOnce = false;
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ResetMoveForwardInput Called!"));
}

void AGameplayPlayerController::OnMoveForwardPressed()
{
	if (!PtrCharacter->bIsDead)
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
}

void AGameplayPlayerController::OnMoveForwardReleased()
{
	if (!PtrCharacter->bIsDead)
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
}

void AGameplayPlayerController::OnJumpBegin()
{
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->ServerRun_OnJumpBegin();
	}
}

void AGameplayPlayerController::OnJumpFinish()
{
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->ServerRun_OnJumpFinish();
	}
}


void AGameplayPlayerController::OnCrouchBegin()
{
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->ServerRun_OnCrounchBegin();
	}
}

void AGameplayPlayerController::OnCrouchExit()
{
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->ServerRun_OnCrounchFinish();
	}
}


void AGameplayPlayerController::OnShowScoreTablePressed()
{
	AGameplayHUD* ptrHUD;
	ptrHUD = Cast<AGameplayHUD>(GetHUD());

	if (ptrHUD != NULL)
	{
		ptrHUD->ShowScoresTable();
	}
}

void AGameplayPlayerController::OnShowScoreTableReleased()
{
	AGameplayHUD* ptrHUD;
	ptrHUD = Cast<AGameplayHUD>(GetHUD());

	if (ptrHUD != NULL)
	{
		ptrHUD->HideScoresTable();
	}
}

void AGameplayPlayerController::OnOpenCloseOptionMenuPressed()
{
	AGameplayHUD* ptrHUD;
	ptrHUD = Cast<AGameplayHUD>(GetHUD());

	if (ptrHUD != NULL)
	{
		ptrHUD->OpenCloseOptionsMenu();
	}
}

void AGameplayPlayerController::Turn(float value)
{
	if (PtrCharacter != NULL)
	{
		if (!PtrCharacter->bIsDead)
		{
			AddYawInput(value);
		}
	}
}


void AGameplayPlayerController::LookUp(float value)
{
	if (PtrCharacter != NULL)
	{
		if (!PtrCharacter->bIsDead)
		{
			AddPitchInput(value);

			PtrCharacter->ServerRun_AddjustPitch();
			PtrCharacter->PitchNotReplicated = UKismetMathLibrary::ClampAngle(PtrCharacter->GetControlRotation().Pitch, -90.f, 90.0f);
		}
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotOne()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotOne Called!"));
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_ONE);
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotTwo()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotTwo Called!"));
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_TWO);
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotThree()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotThree Called!"));
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_THREE);
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotFour()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotFour Called!"));
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_FOUR);
	}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotFive()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotFive Called!"));
	if (!PtrCharacter->bIsDead)
	{
	PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_FIVE);
}
}

void AGameplayPlayerController::OnChooseWeaponFromSlotSix()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnChooseWeaponFromSlotSix Called!"));
	if (!PtrCharacter->bIsDead)
	{
		PtrCharacter->GetWeaponComponent()->SwapWeapons(EWeaponSlot::SLOT_SIX);
	}
}


void AGameplayPlayerController::OnFirePressed()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnFirePressed Called!"));
	if (!PtrCharacter->bIsDead)
	{
		FVector tempLoc = PtrCharacter->GetWeaponMesh()->GetSocketLocation("MuzzleSocket");
		FRotator tempRot = PtrCharacter->GetWeaponMesh()->GetSocketRotation("MuzzleSocket");

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CLIENT LOCATION: X %f Y %f Z %f"), tempLoc.X, tempLoc.Y, tempLoc.Z));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CLIENT ROTATION: X %f Y %f Z %f"), tempRot.Pitch, tempRot.Yaw, tempRot.Roll));
		tempRot.Pitch += 180;
		PtrCharacter->ServerRun_OnFireBegin(tempLoc, tempRot);
	}
}

void AGameplayPlayerController::OnFireReleased()
{
	if (!PtrCharacter->bIsDead)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OnFireReleased Called!"));
	}
}