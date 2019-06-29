// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "WeaponComponent.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"


// MAYBE DELETE THIS
// MAYBE DELETE THIS
// MAYBE DELETE THIS
// MAYBE DELETE THIS
#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Create camera component and attach it into mesh socket
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "CameraSocket");
	CameraComponent->bUsePawnControlRotation = true;
	
	// Create weapon component
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	// Set up character movement component
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;	
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_WALK_SPEED;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MAXIMAL_CROUNCH_SPEED;

	// Create weapon skeleton component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "RifleSocket");

	// Inherited from UrbanOpsCharacter
	CharacterType = ECharacterType::PLAYER_CHARACTER;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, PitchReplicated);
}



// bCanEverTick is dissabled !!!
/*
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/



void APlayerCharacter::ServerRun_AddjustPitch_Implementation()
{
	PitchReplicated = UKismetMathLibrary::ClampAngle(GetControlRotation().Pitch, -90.f, 90.0f);
}

void APlayerCharacter::ServerRun_OnCrounchBegin_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_Crounch_Implementation Called!"));
	Multicast_OnCrounchBegin();
}

void APlayerCharacter::ServerRun_OnCrounchFinish_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_UnCrounch_Implementation Called!"));
	Multicast_OnCrounchFinish();
}

void APlayerCharacter::ServerRun_OnJumpBegin_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnJumpBegin_Implementation Called!"));
	Multicast_OnJumpBegin();
}

void APlayerCharacter::ServerRun_OnJumpFinish_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnJumpFinish_Implementation Called!"));
}

void APlayerCharacter::ServerRun_OnSprintBegin_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnSprintBegin_Implementation Called!"));
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_RUN_SPEED;
	bIsSprintingReplicated = true;
	Multicast_OnSprintBegin();
}

void APlayerCharacter::ServerRun_OnSprintFinish_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnSprintFinish_Implementation Called!"));
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_WALK_SPEED;
	bIsSprintingReplicated = false;
	Multicast_OnSprintFinish();
}

void APlayerCharacter::ServerRun_OnFireBegin_Implementation(FVector testLocation, FRotator testRotation)
{
	// Try and fire a projectile
	if (WeaponComponent->GetProjectileClass() != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//FVector tempLoc = WeaponMesh->GetSocketLocation("MuzzleSocket");
			//FRotator tempRot = WeaponMesh->GetSocketRotation("MuzzleSocket");

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SERVER LOCATION: X %f Y %f Z %f"), testLocation.X, testLocation.Y, testLocation.Z));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SERVER ROTATION: X %f Y %f Z %f"), testRotation.Pitch, testRotation.Yaw, testRotation.Roll));

			// spawn the projectile at the muzzle
			AProjectile* ptrProjectile = World->SpawnActor<AProjectile>(WeaponComponent->GetProjectileClass(), testLocation, testRotation, ActorSpawnParams);
			if (ptrProjectile != NULL)
			{
				ptrProjectile->SetOwner(this);
			}
		}
		GetPlayerState();
	}

	Multicast_PlayFireAndWeaponEffect();

	// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
		{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


bool APlayerCharacter::ServerRun_AddjustPitch_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnCrounchBegin_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnCrounchFinish_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnJumpBegin_Validate()			{ return true; }
bool APlayerCharacter::ServerRun_OnJumpFinish_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnSprintBegin_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnSprintFinish_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnFireBegin_Validate(FVector testLocation, FRotator testRotation)		{ return true; }


void APlayerCharacter::Multicast_OnJumpBegin_Implementation()
{
	Jump();
}


void APlayerCharacter::Multicast_OnCrounchBegin_Implementation()
{
	Crouch();
}


void APlayerCharacter::Multicast_OnCrounchFinish_Implementation()
{
	UnCrouch();
}

void APlayerCharacter::Multicast_OnSprintBegin_Implementation()
{
	bIsSprintingReplicated = true;
}

void APlayerCharacter::Multicast_OnSprintFinish_Implementation()
{
	bIsSprintingReplicated = false;
}

void APlayerCharacter::Multicast_PlayFireAndWeaponEffect_Implementation()
{
	if (WeaponComponent->GetFireSound() != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, WeaponComponent->GetFireSound(), GetActorLocation());
	}
}
