// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UMainMenuWidget::Initialize()
{
	Super::Initialize();
	if (!BTNStartGame->OnClicked.IsBound())
		BTNStartGame->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGame);
	if (!BTNExitGame->OnClicked.IsBound())
		BTNExitGame->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);

	return true;
}

void UMainMenuWidget::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GameLevel");
}

void UMainMenuWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
