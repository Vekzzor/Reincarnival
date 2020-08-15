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
	// Sets default values for this pawn's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void FireRocket();
	UFUNCTION()
	void Strafe(float Value);

	UFUNCTION()
	void AllowFiring();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UShipMovementComponent* ShipMovementComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ShipMesh;

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	// Box collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AttackDelay = 1;

private:
	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY()
	bool canFire = true;
};
