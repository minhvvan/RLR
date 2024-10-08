// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"
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
	//bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	//if (Ret == false)
	//	return false;

	//UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, ESlotType::POST_ITEM_SLOT);
	//if (IsValid(Operation) == false)
	//	return false;

	//UPostItemSlot* DraggedSlot = Cast<UPostItemSlot>(Operation->Master);
	//if (IsValid(DraggedSlot) == false)
	//	return false;

	////만약 옮긴 슬롯에 다른 아이템이 들어가 있다면, 서로 슬롯 위치를 바꿔준다.
	//if (IsEmpty() == false)
	//{
	//	/*
	//		A->B
	//		B->A
	//	*/
	//	GetGameManager()->GetPostalManager()->ChangeItemSlot(GetItemData().ITEM_SEQ, Operation->Master->SlotIndex);
	//	GetGameManager()->GetPostalManager()->ChangeItemSlot(Operation->GetItemData().ITEM_SEQ, SlotIndex);
	//}
	//else
	//{
	//	GetGameManager()->GetPostalManager()->ChangeItemSlot(Operation->GetItemData().ITEM_SEQ, SlotIndex);
	//	//SetItemData(Operation->GetItemData());
	//	DraggedSlot->Clear();
	//}

	////슬롯을 정확하게 옮겼으면, 기존 자리에 있던 슬롯은 깨끗하게 비워준다.
	//PostUI->RefreshUI();

	return true;
}

bool UPostItemSlot::HandleInventoryItemDrop(UBaseDragDropOperation* Operation)
{
	UInventoryManager* InventoryManager = GetGameManager()->GetInventoryManager();
	UPostalManager* PostalManager = GetGameManager()->GetPostalManager();

	if (!IsValid(InventoryManager) || !IsValid(PostalManager))
		return false;

	FItemData DroppedItem = Operation->GetItemData();
	FItemResource DroppedItemResource = Operation->GetItemResource();
	// 우편함에 아이템 추가
	SetItemData(DroppedItem);
	SetSlotItemResourceData(DroppedItemResource);

	// 인벤토리에서 아이템 제거
	InventoryManager->RemoveItem(DroppedItem.ITEM_SEQ);

	// UI 갱신
	PostUI->RefreshUI();

	// PostalManager의 Update 함수 호출
	PostalManager->Update();

	return true;
}

void UPostItemSlot::SetSlot(int64 NewitemId)
{
	UTexture2D* itemTexture = GameInstance->GetDataManager()->GetItemResource(NewitemId).ItemImage;
	FText itemName = GameInstance->GetDataManager()->GetItemData(NewitemId).NAME;
	SetSlotImage(itemTexture);
	ItemNameText->SetText(itemName);
}

void UPostItemSlot::RefreshUI()
{
	Super::RefreshUI();
}

void UPostItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (IsEmpty() == true)
		return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (!GM) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->OpenSubUINearTargetSlot(this, EUIType::ITEM_INFOMATION);
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