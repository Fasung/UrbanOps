// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h" 
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "GameplayPlayerController.h"
#include "UrbanOpsCharacter.h"
#include "GameplayPlayerState.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Set up projectile mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 8.0f;


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//AGameplayPlayerState* ptrPlayerState = Cast<AGameplayPlayerState>(ptrActor->GetController()->PlayerState);

	//AUrbanOpsCharacter* ptrActor = Cast<AUrbanOpsCharacter>(OtherActor);
	//Cast<AUrbanOpsCharacter>(GetOwner());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->bCanBeDamaged)
	{
		AUrbanOpsCharacter* ptrActor = Cast<AUrbanOpsCharacter>(OtherActor);

		// Actor is player character
		if (ptrActor != NULL)
		{
			if (Role == ROLE_Authority)
			{
			// If return true, player is dead
				if (ptrActor->ApplyDamage(10) && ptrActor->IsDead() == false)
				{
					ptrActor->Die_FromServerOnServerOnly();

					AUrbanOpsCharacter* ptrOwningPlayer = Cast<AUrbanOpsCharacter>(GetOwner());
					AGameplayPlayerState* ptrPlayerState = Cast<AGameplayPlayerState>(ptrOwningPlayer->GetPlayerState());
					// Make a check
					if (ptrPlayerState != NULL)
					{
						// Addjust shooter score here
						ptrPlayerState->AddjustKills();
					}


					ptrOwningPlayer = Cast<AUrbanOpsCharacter>(OtherActor);
					ptrPlayerState = Cast<AGameplayPlayerState>(ptrOwningPlayer->GetPlayerState());

					if (ptrPlayerState != NULL)
					{
						// Addjust killed player score here
						ptrPlayerState->AddjustDeads();
					}

				}
			}

			// DEBUGING ONLY, DELETE THIS
			// DEBUGING ONLY, DELETE THIS
			// DEBUGING ONLY, DELETE THIS
			// DEBUGING ONLY, DELETE THIS
			// DEBUGING ONLY, DELETE THIS
			ProjectileMovement->InitialSpeed = 0.f;
			ProjectileMovement->MaxSpeed = 0.f;
			ProjectileMovement->Velocity.X = 0.0f;
			ProjectileMovement->Velocity.Y = 0.0f;
			ProjectileMovement->Velocity.Z = 0.0f;

			// Spawn hit effect

			// Destroy the bullet
			Destroy();

			// Get out from this function
			return;
		}


		// Hitted actor was not player, lets try again

		// Actor is something else
		//if (NO VARIABLE) 
		{
			// Spawn hit effect

			// Destroy the bullet
			Destroy();

			// Get out from this function
			return;
		}
	}

	// Hitted object is not actor, probably just static wall or something else
	// Spawn hit effect

	// Destroy the bullet
	Destroy();
}