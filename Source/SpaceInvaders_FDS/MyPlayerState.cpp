// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Gameplay/Ship.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
AMyPlayerState::AMyPlayerState()
{

}
//TODO
void AMyPlayerState::OutOfLives()
{
	
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	Score = 0.0f;
	APawn* PlayerPawn = GetPawn();
	if (PlayerPawn)
	{
		AShip* Ship = Cast<AShip>(PlayerPawn);
		Ship->CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayerState::OnOverlapBegin);
	}
}


void AMyPlayerState::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->Instigator)
	{
		if (OtherActor->Instigator->ActorHasTag("PlayerShip"))
		{
			
		}
		else if (OtherActor->Instigator->ActorHasTag("AlienShip"))
		{
			//if (GetWorldTimerManager().IsTimerActive(this, InvulnerabilityTimer))
			//{
				Lives--;
				if (Lives <= 0)
					OutOfLives();
			//	GetWorldTimerManager().SetTimer(InvulnerabilityTimer, this, &AAlienController::TryAttack, FMath::FRandRange(AttackDelayMin, AttackDelayMax), true, 2);
			//}
		}
	}
	else
	{
	}
}