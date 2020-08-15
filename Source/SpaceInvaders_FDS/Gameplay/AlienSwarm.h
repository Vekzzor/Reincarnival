// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienShip.h"
#include "AlienSwarm.generated.h"

UCLASS()
class SPACEINVADERS_FDS_API AAlienSwarm : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienSwarm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnWaves();

	UFUNCTION()
		void Descend();
	UFUNCTION()
		void NotifyScreenBoundryOverlap();
	UFUNCTION()
		void NotifyShipDestruction();

	UPROPERTY()
	class UMovementComponent* MovementComponent;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Controller)
	TSubclassOf<class AAlienController> AlienControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int ColumnIncrement = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int RowSize = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int ColumnSize = 1;

	UPROPERTY()
	int Direction = 1;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	int SwarmShipsAlive;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float VelocityScale = 0.2f;

private:

	FVector StartLocation;
	bool StartDescent = false;
	FTimerHandle DescentDelay;
};
