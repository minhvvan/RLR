// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EquipmentList.h"
#include "UI/InGame/Enhancement/EquipmentButton.h"
#include "UI/InGame/Enhancement/EnhanceStatInfo.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/InventoryManager.h"
#include "Structs/ItemStructs.h"

#include "Components/RichTextBlock.h"
#include "Components/Button.h"
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
	int32 EnhanceMaterialID = 16777228;
	/* 슬롯에 있는 아이템 데이터가 ITEM_ID == -1 이면 비어 있는 슬롯으로 처리 중, 일단 물약을 강화재료로 둔다 */
	bool isItemExist  = GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID).ITEM_ID != -1;
	/* TODO : 현재 Inventory에서 Quantity가 합쳐지고 있지 않음. 나중에 필요한 수량으로 바꿔주기*/
	bool isSufficient = GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID).ITEM_QUANTITY >= 1;

	/* TODO : 강화 아이템 설정, 클라와 서버의 ItemID가 통일되면 ITEM_SEQ->Item_ID로 바꿔야함*/
	EnhanceUI->EnhanceSlot_Equip->SetSlot(itemData.ITEM_SEQ);
	EnhanceUI->EnhanceSlot_Equip->SetItemData(itemData);
	/* TODO : 강화 재료 설정, 나중에 ITEM_SEQ->Item_ID로 바꿔야함 */
	EnhanceUI->EnhanceSlot_Item1->SetSlot(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID).ITEM_SEQ);
	EnhanceUI->EnhanceSlot_Item1->SetItemData(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID));
	EnhanceUI->EnhanceSlot_Item2->SetSlot(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID).ITEM_SEQ);
	EnhanceUI->EnhanceSlot_Item2->SetItemData(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID));
	EnhanceUI->EnhanceSlot_Item3->SetSlot(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID).ITEM_SEQ);
	EnhanceUI->EnhanceSlot_Item3->SetItemData(GameInstance->GetInventoryManager()->GetItem(EnhanceMaterialID));

	EnhanceUI->BeforeEnhanceStatInfo->ItemStatusText->SetText(itemData.TEXT);

	/*	강화재료, 재화가 충분하지 않으면 강화버튼 enabled false 
		일단은 TotalMoney검사, 재화가 처음에 0이기 때문에 테스트용으로 0으로 둔다.
	*/
	if(GameInstance->GetPlayerManager()->GetPlayerGood().TotalMoney < 0) return;
	if (isItemExist && isSufficient)
	{
		EnhanceUI->EnhanceButton->SetIsEnabled(true);
	}
	else
	{
		EnhanceUI->EnhanceButton->SetIsEnabled(false);
	}

	/* TODO : 강화 후의 stat text도 설정하기. itemData가 강화데이터를 가지고 있어야하나? */
}
