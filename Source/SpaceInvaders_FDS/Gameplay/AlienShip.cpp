// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienShip.h"
#include "Controllers/AlienController.h"
#include "Engine/Engine.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerState.h"

AAlienShip::AAlienShip()
{
	Tags.Add("AlienShip");
	PrimaryActorTick.bCanEverTick = false;
	// Use a Box as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAlienShip::OnOverlapBegin);
	// Set the box's extent
	CollisionComponent->InitBoxExtent(FVector(24.0f, 33.0f, 3.0f));
	CollisionComponent->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));

	CollisionComponent->BodyInstance.SetCollisionProfileName("OverlapOnlyPawn");

	// Set the root component to be the collision component
	RootComponent = CollisionComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset1(TEXT("/Game/Models/3D_Icons/Alien2.Alien2"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(MeshAsset1.Object);
	ShipMesh->BodyInstance.SetCollisionProfileName("NoCollision");
	ShipMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset2(TEXT("/Game/Models/3D_Icons/Alien1.Alien1"));
	ShipMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh2"));
	ShipMesh2->SetStaticMesh(MeshAsset2.Object);
	ShipMesh2->BodyInstance.SetCollisionProfileName("NoCollision");
	ShipMesh2->SetVisibility(false);
	ShipMesh2->SetupAttachment(RootComponent);
	

	// Create an instance of our movement component, and tell it to update the root
	ShipMovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovementComponent"));
	ShipMovementComponent->UpdatedComponent = RootComponent;
	AIControllerClass = AAlienController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UClass> ProjectileAsset(TEXT("/Game/Blueprints/BP_Bomb.BP_Bomb_C"));
	ProjectileClass = ProjectileAsset.Object;

	MuzzleOffset = FVector(50.0f, 0.0f, 0.0f);
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AAlienShip::BeginPlay()
{
	Super::BeginPlay();
}

void AAlienShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAlienShip::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->Instigator)
	{
		if (OtherActor->Instigator->ActorHasTag("PlayerShip"))
		{
			//Hit by projectile from player
			SetActorTickEnabled(false);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);

			if (OtherActor->Instigator->IsPlayerControlled())
			{
				AMyPlayerState* State = Cast<AMyPlayerState>(OtherActor->Instigator->GetPlayerState());
				if (State)
				{
					State->Score += 1.0f;
				}
			}
		}
	}
}

void AAlienShip::SwapMesh()
{
	if (ShipMesh->IsVisible())
	{
		ShipMesh->SetVisibility(false);
		ShipMesh2->SetVisibility(true);
	}
	else
	{
		ShipMesh->SetVisibility(true);
		ShipMesh2->SetVisibility(false);
	}
}

void AAlienShip::ResetAnimation()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackAnimationTimer);
	ShipMesh->SetVisibility(true);
	ShipMesh2->SetVisibility(false);
}

void AAlienShip::PlayAttackAnimation()
{
	SwapMesh();
	GetWorldTimerManager().SetTimer(AttackAnimationTimer, this, &AAlienShip::SwapMesh, AttackAnimationDuration, false);
}

void AAlienShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAlienShip::DropBomb()
{
	// Attempt to fire a projectile
	if (ProjectileClass)
	{
		// Transform MuzzleOffset to world space
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = GetActorRotation();
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			// Spawn the projectile at the muzzle
			AWeaponProjectile* Projectile = World->SpawnActor<AWeaponProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AAlienShip::Strafe(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}