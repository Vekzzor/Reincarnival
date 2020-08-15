// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_FDS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton* BTNStartGame;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton* BTNExitGame;
	
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void ExitGame();

};
