// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipMovementComponent.h"
#include "WeaponProjectile.h"
#include "Components/BoxComponent.h"
#include "Ship.generated.h"
UCLASS()
class SPACEINVADERS_FDS_API AShip : public APawn
{
	GENERATED_BODY()

public:
	AShip();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	/** Spawn and shoot a rocket*/
	UFUNCTION()
	void FireRocket();

	UFUNCTION()
	void Strafe(float Value);

	/** Lets the ship fire again*/
	UFUNCTION()
	void AllowFiring();

	/** Checks for collisions with ship*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UShipMovementComponent* ShipMovementComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh;

	/** Gun muzzle's offset from the camera location*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** Projectile class to spawn*/
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	/** Box collision component*/
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionComponent;

	/** Delay between attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelay = 1;

private:
	/** Attack timer handle*/
	UPROPERTY()
	FTimerHandle AttackTimer;

	bool CanFire = true;

	bool ShipDestroyed = false;
};
