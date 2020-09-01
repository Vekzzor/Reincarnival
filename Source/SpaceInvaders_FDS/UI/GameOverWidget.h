// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"
#include "GameOverWidget.generated.h"

/**
 * Game over screen
 * Shows the amount of aliens killed
 */
UCLASS()
class REINCARNIVAL_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void ReturnToMainMenu();

	void SetScore(float Score);
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTScore;
};
