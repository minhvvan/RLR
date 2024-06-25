// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/Inventory/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameManager/UIManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/GameManager.h"
#include "UI/InGame/Equipment/EquipmentUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"



void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	Clear();
	
	if (ItemButton)
	{
		ItemButton->OnClicked.AddUniqueDynamic(this, &UInventorySlot::OnClickedItemSlot);
		ItemButton->OnHovered.AddUniqueDynamic(this, &UInventorySlot::OnHoveredItemSlot);
		ItemButton->OnUnhovered.AddUniqueDynamic(this, &UInventorySlot::OnUnHoveredItemSlot);
	}

}

void UInventorySlot::OnClickedItemSlot()
{
	/*
		1.서버에 장착 Req 패킷을 날려준다. 
			PacketHandler->SendEquipItemPacket(ItemData)

		2.서버에서 Equip Item 패킷을 다시 날리면 EquipmentUI에서 해당 슬롯 정보를 업데이트 해준다.
	*/
	if (SlotItemData.ITEM_ID == -1)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("해당 슬롯에는 아이템 정보가 없습니다."));
		return;
	}

	FString ItemName = SlotItemData.NAME;
	UUtilBlueprintFunctionLibrary::DebugLog(ItemName);


	/*
		임시 코드.
		원래라면 서버에 패킷을 보내고 끝내야 하지만, 지금은 서버가 준비가 안되었으므로 클라 내부에서 자체적으로 처리.
	*/

	UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
	if (MainUI)
	{
		UGameManager* GM = Cast<UGameManager>(GetGameInstance());
		if (GM)
		{
			GM->GetInventoryManager()->ItemData[SlotItemData.ITEM_ID].IsEquiped = true;
		}
		MainUI->EquipmentUI->EquipItem(SlotItemData);
		MainUI->InventoryUI->RefreshUI();
	}
}

void UInventorySlot::OnHoveredItemSlot()
{
	if (IsEmpty() == true)
		return;

	UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
	if (MainUI)
	{
		MainUI->ItemInformation->SetItemData(SlotItemData);
		//MainUI->ItemInformation->OpenUIToTop();
		MainUI->ItemInformation->OpenUINearTargetSlot(this);
	}
}

void UInventorySlot::OnUnHoveredItemSlot()
{
	UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
	if (MainUI)
	{
		MainUI->ItemInformation->CloseUI();
	}
}

void UInventorySlot::SetItemData(FItemData ItemData)
{
	//슬롯 정보를 업데이트 해준다.


	SlotItemData = ItemData;

	UTexture2D* Texture = ItemData.ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	ItemImage->SetBrushFromTexture(Texture, true);
	DisplayEquippedItems(ItemData.IsEquiped);

	//아이템 등급에 따른 배경 이미지 색깔 추가해주기.

}

void UInventorySlot::Clear()
{
	if (IsValid(DefaultSlotImage) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::Clear Error. Default Slot Image가 없습니다."));
		return;
	}

	ItemImage->SetBrushFromTexture(DefaultSlotImage, true);

	SlotItemData = FItemData();
}
