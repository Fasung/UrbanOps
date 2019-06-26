// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h" 
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "PlayerCharacter.h"
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


void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Role == ROLE_Authority)
	{
		if (OtherActor->bCanBeDamaged)
		{

			APlayerCharacter* ptrActor;

			ptrActor = Cast<APlayerCharacter>(OtherActor);

			// Actor is player character
			if (ptrActor != NULL)
			{
				AGameplayPlayerState* ptrPlayerState;
				ptrPlayerState = Cast<AGameplayPlayerState>(ptrActor->GetController()->PlayerState);
				if (ptrPlayerState != NULL)
				{
					// If return true, player is dead
					if (ptrPlayerState->DecreaseHealth(1))
					{
						ptrActor->bIsDead = true;
						ptrActor->Multicast_Die();
					}
				}
			}
			else
			{

			}
		}
	}
	//else 	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CLIENT FROM Projectile!"));

	ProjectileMovement->InitialSpeed = 0.f;
	ProjectileMovement->MaxSpeed = 0.f;
	ProjectileMovement->Velocity.X = 0.0f;
	ProjectileMovement->Velocity.Y = 0.0f;
	ProjectileMovement->Velocity.Z = 0.0f;

//	Destroy();
//	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Projectile destroyed!"));
}