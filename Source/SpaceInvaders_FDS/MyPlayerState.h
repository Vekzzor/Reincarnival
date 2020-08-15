// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_FDS_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	AMyPlayerState();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OutOfLives(); //TODO

	UPROPERTY()
	int Lives;//TODO
	UPROPERTY()
	FTimerHandle InvulnerabilityTimer;//TODO

	UPROPERTY()
	float InvulnerabilityDuration;//TODO
};
