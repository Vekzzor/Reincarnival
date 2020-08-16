// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "Gameplay/AlienSwarm.h"
#include "AlienController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPACEINVADERS_FDS_API AAlienController : public AController
{
	GENERATED_BODY()

public:
	AAlienController();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnUnPossess() override;

	/** Checks for collisions with the possessed alien ship*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Check for no friendly fire and drops a bomb*/
	UFUNCTION()
	void TryAttack();

	UFUNCTION()
	void StartAttacking();

	UPROPERTY()
	class AAlienShip* Ship = nullptr;
	UPROPERTY()
	class AAlienSwarm* Swarm = nullptr;

	/** Minimum wait time to try and attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelayMin = 1;
	/** Maximum wait time to try and attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelayMax = 5;
private:
	/** Attack delay timer handle*/
	FTimerHandle AttackTimer;
};
