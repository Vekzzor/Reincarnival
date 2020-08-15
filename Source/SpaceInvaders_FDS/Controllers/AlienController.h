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
	AAlienController(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnUnPossess() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TryAttack();

	UFUNCTION()
	void StartAttacking();

	UPROPERTY()
	class AAlienShip* Ship = nullptr;
	UPROPERTY()
	class AAlienSwarm* Swarm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelayMin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelayMax = 5;
private:

	FTimerHandle AttackTimer;
};
