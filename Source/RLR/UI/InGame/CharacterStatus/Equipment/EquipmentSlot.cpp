// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatus/Equipment/EquipmentSlot.h"
#include "EquipmentSlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "Structs/ItemStructs.h"
#include "Structs/UtilStructs.h"

#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/ItemInformation.h"

UEquipmentSlot::UEquipmentSlot(const FObjectInitializer& ObjectInitializer):
	EquipmentSlotType(EEquipmentType::NONE)
{
}

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::EQUIPMENT_SLOT);

	//SlotButton->OnClicked.AddUniqueDynamic(this, &UEquipmentSlot::OnClickedSlotButton);
	//SlotButton->OnHovered.AddUniqueDynamic(this, &UEquipmentSlot::OnHoveredSlotButton);
	//SlotButton->OnUnhovered.AddUniqueDynamic(this, &UEquipmentSlot::OnUnHoveredSlotButton);
}

void UEquipmentSlot::RefreshUI()
{
	Super::RefreshUI();

	UTexture2D* Texture = GetItemResourceData().ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	SlotImage->SetBrushFromTexture(Texture, true);
}

void UEquipmentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsEmpty() == true)
		return;

	UUIManager* UIManager = GetUIManager();
	if (UIManager == nullptr) return;

	UMainUI* mainUI = UIManager->GetPage<UMainUI>(RLRTAG.Page_InGame);
	if (UIManager == nullptr) return;

	mainUI->OpenSubUINearTargetSlot(this, RLRTAG.UI_ItemInfomation);
}

void UEquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (IsEmpty() == true)
		return;

	UUIManager* UIManager = GameInstance->GetUIManager();
	if (UIManager == nullptr) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();

	UIManager->CloseSubUI(TagManager.UI_ItemInfomation);
}

FReply UEquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//비어 있다면 아무것도 하지 않는다.
	if (IsEmpty() == true)
		return result;

	/*
		서버에 착용 해제 요청을 보낸다.
	*/

	GetNetworkManager()->SendUnEquipChangePacket(GetItemData());

	return result;
}