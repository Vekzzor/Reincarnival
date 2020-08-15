// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameOverWidget.h"
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerHUD::AddGameOverWidget(float Score)
{
	if (GameOverWidgetClass)
	{
		auto GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget->SetScore(Score);
			GameOverWidget->AddToViewport();
			GetWorldTimerManager().SetTimer(EndTimer, GameOverWidget, &UGameOverWidget::ReturnToMainMenu, 5.0f, false);
		}
	}
}
