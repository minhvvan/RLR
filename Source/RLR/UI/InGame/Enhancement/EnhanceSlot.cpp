// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"

void UEnhanceSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::ENHANCE_ITEM_SLOT);
	itemId = -1;
	Clear();
}

void UEnhanceSlot::RefreshUI()
{
	Super::RefreshUI();
}

void UEnhanceSlot::Clear()
{
	Super::Clear();
}

void UEnhanceSlot::SetItemID(int64 NewItemId)
{
	itemId = NewItemId;
}

void UEnhanceSlot::SetSlot(int64 NewitemId)
{
	itemId = NewitemId;
	FString name = this->GetName();
	UTexture2D* itemTexture = GameInstance->GetDataManager()->GetItemResource(NewitemId).ItemImage;
	SetItemData(GameInstance->GetDataManager()->GetItemData(NewitemId));
	SetSlotImage(itemTexture);
}
