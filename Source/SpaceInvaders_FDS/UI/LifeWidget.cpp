// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeWidget.h"

ULifeWidget::ULifeWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

bool ULifeWidget::Initialize()
{
	return true;
}

void ULifeWidget::UpdateLifeCount(int Value)
{
	TXTLives->SetText(FText::AsNumber(Value));
}
