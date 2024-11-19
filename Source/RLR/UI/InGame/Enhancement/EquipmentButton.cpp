// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EquipmentButton.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "Components/Button.h"

void UEquipmentButton::NativeConstruct()
{
	if (EquipButton)
	{
		EquipButton->OnClicked.AddUniqueDynamic(this, &UEquipmentButton::EquipButtonClicked);
	}
}

void UEquipmentButton::SetItemData(const FItemData& NewItemData)
{
	itemData = NewItemData;
	itemID = itemData.ITEM_ID;
}

void UEquipmentButton::SetEnhanceSlot()
{
	EnhanceSlot->SetSlot(itemID);
}

FItemData UEquipmentButton::GetItemData()
{
	return itemData;
}

void UEquipmentButton::EquipButtonClicked()
{
	OnEquipButtonClick.Broadcast(itemData);
}
