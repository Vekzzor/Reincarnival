// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienController.h"
#include "../Gameplay/AlienShip.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "../Gameplay/Ship.h"

AAlienController::AAlienController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAlienController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		Ship = Cast<AAlienShip>(InPawn);
		Ship->CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAlienController::OnOverlapBegin);
	}
}

void AAlienController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAlienController::OnUnPossess()
{
	Super::OnUnPossess();
	Ship = nullptr;
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
}

void AAlienController::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->Instigator)
	{
		if (OtherActor->Instigator->ActorHasTag("PlayerShip"))
		{
			GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
			Ship->ResetAnimation();
			Swarm->NotifyShipDestruction();
		}
	}
	else
	{
		Swarm->NotifyScreenBoundryOverlap();
	}
}

void AAlienController::TryAttack()
{
	if (Ship)
	{
		// Try and shot at a physics object
		FHitResult Output;
		const FVector Start = Ship->GetActorLocation() + FTransform(Ship->GetActorRotation()).TransformVector(Ship->MuzzleOffset);
		const FVector End = ((Ship->GetActorForwardVector() * 1000) + Start);
		FCollisionQueryParams CollisionParams;
		if (GetWorld()->LineTraceSingleByChannel(Output, Start, End, ECC_Visibility, CollisionParams))
		{
			
			if (Output.bBlockingHit)
			{
				AActor* OtherActor = Output.GetActor();
				UPrimitiveComponent* OtherComp = Output.GetComponent();
				//Don't drop bombs if alien is in the way
				if (!OtherActor->ActorHasTag("AlienShip"))
				{
					Ship->PlayAttackAnimation();
					Ship->DropBomb();
				}
			}
		}
		else
		{
			Ship->PlayAttackAnimation();
			Ship->DropBomb();
		}
	}
}

void AAlienController::StartAttacking()
{
	if (Ship)
	{
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AAlienController::TryAttack, FMath::FRandRange(AttackDelayMin, AttackDelayMax), true);
	}
}

