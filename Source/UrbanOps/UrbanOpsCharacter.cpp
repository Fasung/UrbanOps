// Fill out your copyright notice in the Description page of Project Settings.


#include "UrbanOpsCharacter.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "UnrealNetwork.h"

// Sets default values
AUrbanOpsCharacter::AUrbanOpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsDead = false;
	CurrentHealth = 100;
	MaximalHealth = 100;
	CurrentStamina = 100;
	MaximalStamina = 100;
}

// Called when the game starts or when spawned
void AUrbanOpsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUrbanOpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUrbanOpsCharacter::Respawn()
{

}

void AUrbanOpsCharacter::Die_FromServerOnServerOnly()
{
	bIsDead = true;
	SetReplicateMovement(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Multicast_Die();
}

void AUrbanOpsCharacter::Multicast_Die_Implementation()
{
	bIsDead = true;
	SetReplicateMovement(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetAllBodiesBelowSimulatePhysics("Hips", true, true);
}

bool AUrbanOpsCharacter::ApplyDamage(uint8 value)
{
	this->CurrentHealth -= value;
	if (this->CurrentHealth < 1)
	{
		this->CurrentHealth = 0;
		return true;
	}
	else return false;
}


void AUrbanOpsCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUrbanOpsCharacter, CurrentHealth);
	DOREPLIFETIME(AUrbanOpsCharacter, CurrentStamina);
}