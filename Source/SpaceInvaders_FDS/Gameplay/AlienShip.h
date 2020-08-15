// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WeaponProjectile.h"
#include "ShipMovementComponent.h"
#include "Components/BoxComponent.h"
#include "AlienShip.generated.h"

UCLASS()
class SPACEINVADERS_FDS_API AAlienShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAlienShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DropBomb();

	void Strafe(float Value);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SwapMesh();

	UFUNCTION()
	void ResetAnimation();

	UFUNCTION()
	void PlayAttackAnimation();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UShipMovementComponent* ShipMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh2;

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	// Box collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionComponent;

	UPROPERTY()
	FTimerHandle AnimationTimer;

	UPROPERTY()
	float AnimationDuration = 0.5f;
};
