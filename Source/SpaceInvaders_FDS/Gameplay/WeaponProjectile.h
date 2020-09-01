// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class REINCARNIVAL_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Checks for collisions with projectile*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** initializes the projectile's velocity in the shoot direction*/
	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);

	/** Box collision component*/
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;
};
