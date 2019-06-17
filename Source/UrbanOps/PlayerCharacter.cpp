// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"


// MAYBE DELETE THIS
#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	//bReplicates = true;

	// Create local player mesh without head
	MeshNoHead = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("CharacterMeshNoHead");
	if (MeshNoHead)
	{
		MeshNoHead->AlwaysLoadOnClient = true;
		MeshNoHead->AlwaysLoadOnServer = true;
		MeshNoHead->bOwnerNoSee = false;
		MeshNoHead->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		MeshNoHead->bCastDynamicShadow = true;
		MeshNoHead->bAffectDynamicIndirectLighting = true;
		MeshNoHead->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MeshNoHead->SetupAttachment(GetCapsuleComponent());
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		MeshNoHead->SetCollisionProfileName(MeshCollisionProfileName);
		MeshNoHead->SetGenerateOverlapEvents(false);
		MeshNoHead->SetCanEverAffectNavigation(false);
	}

	// Create camera component and attach it into mesh socket
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(MeshNoHead, FAttachmentTransformRules::SnapToTargetIncludingScale, "CameraSocket");
	CameraComponent->bUsePawnControlRotation = true;

	// Set up character movement component
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;	
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_WALK_SPEED;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MAXIMAL_CROUNCH_SPEED;
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
//	DOREPLIFETIME(APlayerCharacter, bIsDeadReplicated);
//	DOREPLIFETIME(APlayerCharacter, bIsJumpingReplicated);
//	DOREPLIFETIME(APlayerCharacter, bIsSprintingReplicated);
}


/*
// bCanEverTick is dissabled !!!
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_Crounch_Implementation Called!"));
	Multicast_OnCrounchBegin();
}

void APlayerCharacter::ServerRun_OnCrounchFinish_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_UnCrounch_Implementation Called!"));
	Multicast_OnCrounchFinish();
}

void APlayerCharacter::ServerRun_OnJumpBegin_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnJumpBegin_Implementation Called!"));
	Multicast_OnJumpBegin();
}

void APlayerCharacter::ServerRun_OnJumpFinish_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnJumpFinish_Implementation Called!"));
}

void APlayerCharacter::ServerRun_OnSprintBegin_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnSprintBegin_Implementation Called!"));
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_RUN_SPEED;
	bIsSprintingReplicated = true;
}

void APlayerCharacter::ServerRun_OnSprintFinish_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: ServerRun_OnSprintFinish_Implementation Called!"));
	GetCharacterMovement()->MaxWalkSpeed = MAXIMAL_WALK_SPEED;
	bIsSprintingReplicated = false;
}

bool APlayerCharacter::ServerRun_AddjustPitch_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnCrounchBegin_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnCrounchFinish_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnJumpBegin_Validate()			{ return true; }
bool APlayerCharacter::ServerRun_OnJumpFinish_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnSprintBegin_Validate()		{ return true; }
bool APlayerCharacter::ServerRun_OnSprintFinish_Validate()		{ return true; }



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