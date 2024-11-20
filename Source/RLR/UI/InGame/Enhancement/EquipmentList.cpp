// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EquipmentList.h"
#include "UI/InGame/Enhancement/EquipmentButton.h"
#include "UI/InGame/Enhancement/EnhanceStatInfo.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "Components/RichTextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UEquipmentList::NativeConstruct()
{
}
/* 강화창의 장비목록에 장비아이템 추가 */
void UEquipmentList::AddEquipButton(FItemData& itemData)
{
	if (EquipListContainer && EquipButtonUIClass)
	{
		UEquipmentButton* EquipButton = CreateWidget<UEquipmentButton>(this, EquipButtonUIClass);
		if (EquipButton)
		{
			EquipButton->SetItemData(itemData);
			EquipButton->SetEnhanceSlot();
			EquipButton->EnhanceSlot->SetItemData(itemData);
			//EquipButton->EnhanceLevelText->SetText()
			EquipButton->EquipmentNameText->SetText(itemData.NAME);

			EquipButton->OnEquipButtonClick.AddUniqueDynamic(this, &UEquipmentList::OnEquipItemClicked);
			EquipListContainer->AddChild(EquipButton);
		}
	}
}
/* 장비아이템이 클릭되었을 때 */
void UEquipmentList::OnEquipItemClicked(FItemData& itemData)
{
	EnhanceUI->EnhanceSlot_Equip->SetSlot(itemData.ITEM_ID);
	EnhanceUI->EnhanceSlot_Equip->SetItemData(itemData);

	EnhanceUI->BeforeEnhanceStatInfo->ItemStatusText->SetText(itemData.TEXT);
	/* TODO : 강화 후의 stat text도 설정하기 */
}
