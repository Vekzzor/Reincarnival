// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_FDS_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;

	UFUNCTION()
	void AddGameOverWidget(float Score);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LifeWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	FTimerHandle EndTimer;
};
