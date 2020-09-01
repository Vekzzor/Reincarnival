// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WeaponProjectile.h"
#include "ShipMovementComponent.h"
#include "Components/BoxComponent.h"
#include "AlienShip.generated.h"

UCLASS()
class REINCARNIVAL_API AAlienShip : public APawn
{
	GENERATED_BODY()

public:
	AAlienShip();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Spawn and drop a bomb*/
	UFUNCTION()
	void DropBomb();

	UFUNCTION()
	void Strafe(float Value);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SwapMesh();

	UFUNCTION()
	void ResetAnimation();

	UFUNCTION()
	void PlayAttackAnimation();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UShipMovementComponent* ShipMovementComponent;

	/** Default ship mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh;

	/** Mesh to use when attacking*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh2;

	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** Projectile class to spawn*/
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	// Box collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionComponent;
	
	/** Duration to stay in the attack animation*/
	UPROPERTY()
	float AttackAnimationDuration = 0.5f;

	/** Attack animation timer handle*/
	UPROPERTY()
	FTimerHandle AttackAnimationTimer;

};
