// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienSwarm.h"
#include "Controllers/AlienController.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
AAlienSwarm::AAlienSwarm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	AlienControllerClass = AAlienController::StaticClass();
	// Create an instance of our movement component, and tell it to update the root.
	MovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AAlienSwarm::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	SpawnWaves();
}

// Called every frame
void AAlienSwarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// add movement in that direction
	AddMovementInput(GetActorRightVector(), Direction*VelocityScale);

}

void AAlienSwarm::SpawnWaves()
{
	TArray<AActor*> Actors;
	GetAttachedActors(Actors);
	int PooledShips = Actors.Num();
	for (int I = 0; I < RowSize; I++)
	{
		for (int K = 0; K < ColumnSize; K++)
		{
			FVector SpawnLoc = FVector(0.0f + K * 100.0f, 0.0f + I * 80.0f, 0.0f);
			AAlienShip* ship = nullptr;
			AAlienController* AlienController = nullptr;
			if (PooledShips <= 0)
			{
				//Pool emptied so we spawn more ships
				ship = GetWorld()->SpawnActor<AAlienShip>(AAlienShip::StaticClass(), SpawnLoc, FRotator::ZeroRotator);
				ship->AIControllerClass = AlienControllerClass;
				AlienController = GetWorld()->SpawnActor<AAlienController>(AlienControllerClass, FVector::ZeroVector, FRotator::ZeroRotator);
				AlienController->Possess(ship);
				AlienController->Swarm = this;
				ship->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			}
			else
			{
				ship = Cast<AAlienShip>(Actors[PooledShips-1]);
				AlienController = Cast<AAlienController>(ship->Controller);
				ship->SetActorHiddenInGame(false);
				ship->SetActorEnableCollision(true);
				PooledShips--;
			}
			
			ship->SetActorRelativeLocation(SpawnLoc);
			AlienController->StartAttacking();
		}	
	}
	SwarmShipsAlive = RowSize*ColumnSize;
	SetActorLocation(StartLocation);
	Direction = 1;
}

void AAlienSwarm::Descend()
{
	Direction *= -1;
	TeleportTo(GetActorLocation() + FVector(-20.0f, 0.0f, 0.0f), GetActorRotation());
	StartDescent = false;
}

void AAlienSwarm::NotifyScreenBoundryOverlap()
{
	if (!StartDescent)
	{
		StartDescent = true;
		GetWorldTimerManager().SetTimerForNextTick(this, &AAlienSwarm::Descend);
	}
}

void AAlienSwarm::NotifyShipDestruction()
{
	SwarmShipsAlive--;

	if (SwarmShipsAlive == 0)
	{
		ColumnSize += ColumnIncrement;
		SpawnWaves();
	}
}

