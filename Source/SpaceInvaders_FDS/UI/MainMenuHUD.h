// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "MainMenuHUD.generated.h"


UCLASS()
class SPACEINVADERS_FDS_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
