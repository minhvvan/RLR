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

	UTexture2D* Texture = GetItemData().ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	SlotImage->SetBrushFromTexture(Texture, true);
}

void UEquipmentSlot::OnClickedSlotButton()
{
	Super::OnClickedSlotButton();

	//비어 있다면 아무것도 하지 않는다.
	if(IsEmpty() == true)
		return;

	/*
		서버에 착용 해제 요청을 보낸다.
	*/

	GetNetworkManager()->SendUnEquipChangePacket(GetItemData());
}

void UEquipmentSlot::OnHoveredSlotButton()
{
	Super::OnHoveredSlotButton();

	if(IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this, EUIType::ITEMINFOMATION);
}

void UEquipmentSlot::OnUnHoveredSlotButton()
{
	Super::OnUnHoveredSlotButton();

	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->CloseSubUI(EUIType::ITEMINFOMATION);
}
