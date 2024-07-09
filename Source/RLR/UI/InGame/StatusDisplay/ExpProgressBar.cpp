// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/ExpProgressBar.h"
#include "Components/ProgressBar.h"
#include "ExpProgressBar.h"

void UExpProgressBar::SetExpPercent(float Value)
{
	if(Value < 0)
		Value = 0;

	ExpProgressBar->SetPercent(Value);
}
