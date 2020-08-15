// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
void AMainMenuHUD::BeginPlay()
{
	if (MainMenuWidgetClass)
	{
		auto MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
