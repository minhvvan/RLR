// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EquipmentButton.h"

#include "Components/Button.h"

void UEquipmentButton::NativeConstruct()
{
	if (EquipButton)
	{
		EquipButton->OnClicked.AddUniqueDynamic(this, &UEquipmentButton::EquipButtonClicked);
	}
}

void UEquipmentButton::SetItemID(int64 NewItemID)
{
	itemID = NewItemID;
}

int64 UEquipmentButton::GetItemID()
{
	return itemID;
}

void UEquipmentButton::EquipButtonClicked()
{
	OnEquipButtonClick.Broadcast(itemID);
}
