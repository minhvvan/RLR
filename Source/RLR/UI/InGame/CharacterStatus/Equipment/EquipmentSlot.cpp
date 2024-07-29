// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatus/Equipment/EquipmentSlot.h"
#include "EquipmentSlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemButton->OnClicked.AddUniqueDynamic(this, &UEquipmentSlot::OnClickedItemSlot);
	ItemButton->OnHovered.AddUniqueDynamic(this, &UEquipmentSlot::OnHoveredItemSlot);
	ItemButton->OnUnhovered.AddUniqueDynamic(this, &UEquipmentSlot::OnUnHoveredItemSlot);
}

void UEquipmentSlot::OnClickedItemSlot()
{
	//비어 있다면 아무것도 하지 않는다.
	if(IsEmpty() == true)
		return;

	/*
		서버에 착용 해제 요청을 보낸다.
			PacketHandler->SendUnEquipItemPacket();
	*/


	/*
		임시 코드. 서버에서 아이템 착용 관련 기능이 완성되면 삭제될 예정.
	*/

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM)
	{
		GM->GetInventoryManager()->ItemData[SlotItemData.ITEM_ID].IsEquiped = false;

		UInGameMainUI* MainUI = Cast<UInGameMainUI>(GetUIManager()->GetMainUI());
		MainUI->InventoryUI->RefreshUI();
	}
	Clear();
}

void UEquipmentSlot::OnHoveredItemSlot()
{
	if(IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this, EUIType::ITEMINFOMATION);
}

void UEquipmentSlot::OnUnHoveredItemSlot()
{
	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->CloseSubUI(EUIType::ITEMINFOMATION);
}

void UEquipmentSlot::SetItemData(FItemData ItemData)
{
	SlotItemData = ItemData;

	UTexture2D* Texture = ItemData.ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	SlotImage->SetBrushFromTexture(Texture, true);

}

void UEquipmentSlot::Clear()
{
	if (IsValid(DefaultSlotImage) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::Clear Error. Default Slot Image가 없습니다."));
		return;
	}

	SlotImage->SetBrushFromTexture(DefaultSlotImage, true);

	SlotItemData = FItemData();
}
