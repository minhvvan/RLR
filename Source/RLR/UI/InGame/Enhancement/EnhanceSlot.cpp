// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"

void UEnhanceSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::ENHANCE_ITEM_SLOT);
	Clear();
}

void UEnhanceSlot::RefreshUI()
{
	Super::RefreshUI();
	Clear();
}

void UEnhanceSlot::Clear()
{
	Super::Clear();
}

void UEnhanceSlot::SetSlot(int64 NewitemId)
{
	UTexture2D* itemTexture = GameInstance->GetDataManager()->GetItemResource(NewitemId).ItemImage;
	SetItemData(GameInstance->GetDataManager()->GetItemData(NewitemId));
	SetSlotImage(itemTexture);
}
