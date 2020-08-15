// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Kismet/KismetSystemLibrary.h"
void UGameOverWidget::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}


void UGameOverWidget::SetScore(float Score)
{
	TXTScore->SetText(FText::AsNumber(Score));
}