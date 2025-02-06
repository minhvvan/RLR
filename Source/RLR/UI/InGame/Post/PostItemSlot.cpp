// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/PostalManager.h"
#include "Structs/UtilStructs.h"

void UPostItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::POST_ITEM_SLOT);
	Clear();
}

void UPostItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UPostItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	HandleInventoryItemDrop(InGeometry, InDragDropEvent, InOperation);

	return true;
}

bool UPostItemSlot::HandleInventoryItemDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UBaseDragDropOperation* Operation = Cast<UBaseDragDropOperation>(InOperation);
	if (!Operation || !Operation->Payload)
		return false;

	// 드래그된 데이터 확인
	UInventorySlot* DraggedSlot = Cast<UInventorySlot>(Operation->Payload);
	if (!DraggedSlot || DraggedSlot->IsEmpty())
		return false;

	// PostItemSlot에 데이터 설정
	SetItemData(DraggedSlot->GetItemData());
	SetSlotImage(DraggedSlot->GetItemResourceData().ItemImage);
	//ItemNameText->SetText(DraggedSlot->GetItemData().NAME);

	// 드래그된 인벤토리 슬롯 비우기
	DraggedSlot->Clear();

	return true;
}

void UPostItemSlot::SetSlot(int64 NewitemId)
{
	UTexture2D* itemTexture = GameInstance->GetDataManager()->GetItemResource(NewitemId).ItemImage;
	FText itemName = GameInstance->GetDataManager()->GetItemData(NewitemId).NAME;
	SetSlotImage(itemTexture);
	/*ItemNameText->SetText(itemName);*/
}

void UPostItemSlot::Clear()
{
	Super::Clear();
}

void UPostItemSlot::RefreshUI()
{
	Super::RefreshUI();

	FItemData itemData = GetItemData();
	TxtItemCount->SetText(FText::AsNumber(itemData.ITEM_QUANTITY));
}

void UPostItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (IsEmpty() == true)
		return;

	UUIManager* UIManager = GetUIManager();
	if (UIManager == nullptr) return;

	UMainUI* mainUI = UIManager->GetPage<UMainUI>(RLRTAG.Page_InGame);
	if (UIManager == nullptr) return;

	mainUI->OpenSubUINearTargetSlot(this, RLRTAG.UI_ItemInfomation);
}

void UPostItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	UIManager->CloseSubUI(TagManager.UI_ItemInfomation);
}

FReply UPostItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (IsEmpty() == true)
	{
		return result;
	}
	FItemData itemData = GetItemData();
	return result;
}

void UPostItemSlot::SetItemAmountShow(bool bVisible)
{
	if (bVisible) TxtItemCount->SetVisibility(ESlateVisibility::Visible);
	else TxtItemCount->SetVisibility(ESlateVisibility::Hidden);
}

void UPostItemSlot::SetInventorySlotIndex(int32 index)
{
	inventorySlotIndex = index;
}

int32 UPostItemSlot::GetInventorySlotIndex()
{
	return inventorySlotIndex;
}