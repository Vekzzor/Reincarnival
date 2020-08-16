// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"
#include "Engine/Engine.h"

AWeaponProjectile::AWeaponProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	// Set the box's extent
	CollisionComponent->InitBoxExtent(FVector(1.0f, 1.0f, 1.0f));

	CollisionComponent->BodyInstance.SetCollisionProfileName("OverlapAll");
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponProjectile::OnOverlapBegin);
	
	// Set the root component to be the collision component
	RootComponent = CollisionComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("NoCollision");

	// Use this component to drive this projectile's movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 300.0f;
	ProjectileMovementComponent->MaxSpeed = 300.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->Bounciness = 0.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

}


void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Ignore overlaps with its own instigator and other actors with the same instigator 
	if (Instigator != OtherActor || !(OtherActor->Instigator && Instigator == OtherActor->Instigator))
	{
		Destroy();
	}
}

void AWeaponProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

