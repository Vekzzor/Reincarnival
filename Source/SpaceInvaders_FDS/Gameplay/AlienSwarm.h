// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienShip.h"
#include "AlienSwarm.generated.h"

UCLASS()
class REINCARNIVAL_API AAlienSwarm : public APawn
{
	GENERATED_BODY()
	
public:	
	AAlienSwarm();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnWaves();

	UFUNCTION()
	void Descend();

	/** Alien ship in swarm hit a level boundry wall*/
	UFUNCTION()
	void NotifyScreenBoundryOverlap();

	/** Alien ship in swarm has been destroyed*/
	UFUNCTION()
	void NotifyShipDestruction();

	UPROPERTY()
	class UMovementComponent* MovementComponent;

	/** Controller class for the aliens */
	UPROPERTY(EditAnywhere, Category = Controller)
	TSubclassOf<class AAlienController> AlienControllerClass;

	/** The ammount of aliens to spawn each row */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int RowSize = 1;
	/** The ammount of rows of aliens to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int ColumnSize = 1;
	/** Increment to add aliens to swarm after each wave */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int ColumnIncrement = 1;

	/** The ammount of aliens left alive in the swarm*/
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	int SwarmShipsAlive;

	/** The velocity scale the swarm strafes with*/
	UPROPERTY(EditAnywhere, Category = Gameplay)
	float VelocityScale = 0.2f;

private:
	/** Current strafing direction*/
	int Direction = 1;
	/** Start location of the swarm on spawn*/
	FVector StartLocation;

	bool StartDescent = false;

	FTimerHandle DescentDelay;
};
