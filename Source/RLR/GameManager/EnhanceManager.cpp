// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/EnhanceManager.h"

void UEnhanceManager::SetEnhanceInfo(FItemData EnhancedItemResult)
{
	EnhancedItemData = EnhancedItemResult;
}

FItemData UEnhanceManager::GetEnhanceInfo()
{
	return EnhancedItemData;
}