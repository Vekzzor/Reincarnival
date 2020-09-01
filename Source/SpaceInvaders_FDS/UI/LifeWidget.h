// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "LifeWidget.generated.h"

//TODO
UCLASS()
class REINCARNIVAL_API ULifeWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	ULifeWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTLives;

	UFUNCTION()
	void UpdateLifeCount(int Value);
};
