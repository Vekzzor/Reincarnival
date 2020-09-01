// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * Controller for when navigating the main menu
 */
UCLASS()
class REINCARNIVAL_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

	virtual void BeginPlay() override;
};
