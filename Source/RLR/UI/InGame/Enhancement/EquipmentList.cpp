// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EquipmentList.h"
#include "UI/InGame/Enhancement/EquipmentButton.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "Components/VerticalBox.h"

void UEquipmentList::NativeConstruct()
{
}
/* 강화창의 장비목록에 장비아이템 추가 */
void UEquipmentList::AddEquipButton(int64 itemID)
{
	AsyncTask(ENamedThreads::GameThread, [this, itemID]()
		{
			if (EquipListContainer && EquipButtonUIClass)
			{
				UEquipmentButton* EquipButton = CreateWidget<UEquipmentButton>(this, EquipButtonUIClass);
				if (EquipButton)
				{
					EquipButton->SetItemID(itemID);
					EquipButton->OnEquipButtonClick.AddUniqueDynamic(this, &UEquipmentList::OnEquipItemClicked);
					EquipListContainer->AddChild(EquipButton);
				}
			}
		});
}
/* 장비아이템이 클릭되었을 때 */
void UEquipmentList::OnEquipItemClicked(int64 itemID)
{
	EnhanceUI->EnhanceSlot_Equip->SetSlot(itemID);
}
