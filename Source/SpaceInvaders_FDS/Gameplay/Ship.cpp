// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerState.h"
#include "UI/PlayerHUD.h"
// Sets default values
AShip::AShip()
{
	Tags.Add("PlayerShip");
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// Set the box's extent.
	CollisionComponent->InitBoxExtent(FVector(12.0f, 38.0f, 3.0f));
	CollisionComponent->BodyInstance.SetCollisionProfileName("Pawn");
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AShip::OnOverlapBegin);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Models/3D_Icons/Ship.Ship"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(MeshAsset.Object);
	ShipMesh->BodyInstance.SetCollisionProfileName("NoCollision");

	ShipMesh->SetRelativeLocation(FVector(11.0f, 0.0f, 0.0f));
	ShipMesh->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
	ShipMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UClass> ProjectileAsset(TEXT("/Game/Blueprints/BP_Rocket.BP_Rocket_C"));
	ProjectileClass = ProjectileAsset.Object;

	// Create an instance of our movement component, and tell it to update the root.
	ShipMovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovementComponent"));
	ShipMovementComponent->UpdatedComponent = RootComponent;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShip::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->Instigator)
	{
		if (OtherActor->Instigator->ActorHasTag("PlayerShip"))
		{
		}
		else if (OtherActor->Instigator->ActorHasTag("AlienShip"))
		{
			if (Controller->IsPlayerController())
			{
				APlayerHUD* HUD = Cast<APlayerHUD>(Cast<APlayerController>(Controller)->GetHUD());
				APlayerState* State = Cast<APlayerState>(GetPlayerState());

				if (HUD && State)
				{
					//Player hit, game over
					HUD->AddGameOverWidget(State->Score);
				}
			}
		}
	}
}

void AShip::FireRocket()
{
	// Attempt to fire a projectile.
	if (ProjectileClass && canFire)
	{
		// Transform MuzzleOffset to world space.
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = GetActorRotation();
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			// Spawn the projectile at the muzzle.
			AWeaponProjectile* Projectile = World->SpawnActor<AWeaponProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				canFire = false;
				GetWorldTimerManager().SetTimer(AttackTimer, this, &AShip::AllowFiring, AttackDelay, false);
			}
		}
	}
}

void AShip::Strafe(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShip::AllowFiring()
{
	canFire = true;
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Strafe", this, &AShip::Strafe);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip::FireRocket);
}

