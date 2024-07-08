// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameMenu/InGameMenuTabList.h"
#include "Components/Button.h"

void UInGameMenuTabList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGameMenuTabList::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInGameMenuTabList::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

