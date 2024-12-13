// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/EnhanceManager.h"

#include "UI/InGame/Enhancement/EnhanceOverlayUI.h"
#include "UI/InGame/Enhancement/EnhanceResultUI.h"

void UEnhanceManager::SetEnhanceInfo(FItemData EnhancedItemResult)
{
	EnhancedItemData = EnhancedItemResult;
}

FItemData UEnhanceManager::GetEnhanceInfo()
{
	return EnhancedItemData;
}

void UEnhanceManager::OpenSuccessUI()
{
	if (EnhanceOverlayUI)
	{
		EnhanceOverlayUI->OpenSuccessUI();
	}
}

void UEnhanceManager::OpenFailUI()
{
	if (EnhanceOverlayUI)
	{
		EnhanceOverlayUI->OpenFailUI();
	}
}