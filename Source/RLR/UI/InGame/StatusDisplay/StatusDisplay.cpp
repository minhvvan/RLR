// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/StatusDisplay.h"

void UStatusDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::STATUSDISPLAY);
}
