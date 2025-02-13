// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/InventoryManager.h"

#include "UI/DialogueUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostAlertUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"

#include "Structs/SkillStructs.h"
#include "Components/GridPanel.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostalManager::Update()
{
	OnUpdatePostalDelegateBroadcast();
}

void UPostalManager::SetRecvPostData(const TArray<FPostResult>& NewPostResult)
{
	PostRecvData = NewPostResult;
	if (PostUIClass)
	{
		PostUIClass->SetRecvPostData(PostRecvData);
	}
}

void UPostalManager::SetSentPostData(const TArray<FPostResult>& NewPostResult)
{
	PostSentData = NewPostResult;
	if (PostUIClass)
	{
		PostUIClass->SetSentPostData(PostSentData);
	}
}

void UPostalManager::SetAlertPostData(const FPostResult& NewPostResult)
{
	PostAlertData = NewPostResult;

	CreateAlertPost();
}

void UPostalManager::CreateAlertPost()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			TSubclassOf<UPostAlertUI> PostAlertUIClass = GameInstance->GetDataManager()->GetWidgetClass<UPostAlertUI>(RLRLITERAL.WBP_PostAlertUI);
			if (PostAlertUIClass)
			{
				UWorld* World = GameInstance->GetWorld();
				if (!World) return;

				// CreateWidget을 위한 적절한 World Context 제공
				UPostAlertUI* NewPostAlertUI = CreateWidget<UPostAlertUI>(World, PostAlertUIClass);
				if (!NewPostAlertUI) return;

				NewPostAlertUI->UpdatePost(PostAlertData);

				NewPostAlertUI->AddToViewport();

				if (IsValid(NewPostAlertUI))
				{
					NewPostAlertUI->UpdatePostItemSlot(PostAlertData);
				}
			}
		});
}

const TArray<FPostResult>& UPostalManager::GetSentPostData() const
{
	return PostSentData;
}

const TArray<FPostResult>& UPostalManager::GetReceivedPostData() const
{
	return PostRecvData;
}

const FPostResult& UPostalManager::GetAlertPostData() const
{
	return PostAlertData;
}

FItemData UPostalManager::GetItemDataById(int64 ItemId)
{
	if (ItemData.Contains(ItemId))
	{
		return ItemData[ItemId];
	}
	return FItemData::EmptyItemData;
}

//void UPostalManager::SetItemData(int64 ItemId, const FItemData& ItemData)
//{
//}

void UPostalManager::AddToPostDeletionList(const FPostResult& PostData, bool IsSent)
{
	if (IsSent)
		SentPostDeletionList.Add(PostData);
	else
		RecvPostDeletionList.Add(PostData);
}

void UPostalManager::ClearPostDeletionList(bool IsSent)
{
	if (IsSent)
		SentPostDeletionList.Empty();
	else
		RecvPostDeletionList.Empty();
}

TArray<FPostResult> UPostalManager::GetAndClearPostDeletionList(bool IsSent)
{
	if (IsSent)
	{
		TArray<FPostResult> TempList = SentPostDeletionList;
		SentPostDeletionList.Empty();
		return TempList;
	}
	else
	{
		TArray<FPostResult> TempList = RecvPostDeletionList;
		RecvPostDeletionList.Empty();
		return TempList;
	}
}

void UPostalManager::OnPostItemSlotClicked(int32 InventorySlotIndex, int32 PostSlotIndex, const FItemData& itemData, ESlotType SlotType)
{
	/* 
		InventoryUI의 해당 SlotIndex에 있는 아이템을 이전으로 돌려놓기 
		개수가 2개 이상이었을 경우 -> 개수 추가
		개수가 1개 이었을 경우 -> 해당 slotIndex에 itemData 추가하기
	*/
	UPostOverlayUI* PostUI = GameInstance->GetUIManager()->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if(!PostUI) return;
	UPostWriteTabWidget* PostWriteWidget = PostUI->PostWriteTabWidget;
	if(!PostWriteWidget) return;
	if (!GetPostWriteTabItemSlot(PostSlotIndex)) return;
	
	UInventorySlot* inventorySlot = GameInstance->GetInventoryManager()->GetInventorySlot(InventorySlotIndex);
	if (inventorySlot->GetItemData().ITEM_QUANTITY >= 1)
	{
		FItemData NewItemData = inventorySlot->GetItemData();
		inventorySlot->SetItemData(NewItemData);
		inventorySlot->CancelSelected();

		UPostItemSlot* PostSlot = GetPostWriteTabItemSlot(PostSlotIndex);
		PostSlot->SetItemData(FItemData::EmptyItemData);
		PostSlot->Clear();
	}
}

UPostItemSlot* UPostalManager::GetPostWriteTabItemSlot(int32 PostItemSlotIndex)
{
	UPostOverlayUI* PostUI = GameInstance->GetUIManager()->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if(!PostUI) return nullptr;
	UPostWriteTabWidget* PostWriteWidget = PostUI->PostWriteTabWidget;
	if(!PostWriteWidget) return nullptr;

	if (PostItemSlotIndex >= PostWriteWidget->PostSlotGridPanel->GetChildrenCount()) return nullptr;
	UPostItemSlot* PostItemSlot = Cast<UPostItemSlot>(PostWriteWidget->PostSlotGridPanel->GetChildAt(PostItemSlotIndex));
	return PostItemSlot;
}

void UPostalManager::OnUpdatePostalDelegateBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdatePostalDelegate.Broadcast();
		});
}

void UPostalManager::SetItemData(int32 itemId)
{
	//ItemData[itemId] = Item;
	FItemData Data = GameInstance->GetDataManager()->GetItemData(itemId);
	ItemData.Add(itemId, Data);

	// ItemValues 맵에 itemId가 이미 존재하면 카운트 증가, 아니면 1로 초기화
	if (ItemValues.Contains(itemId))
	{
		ItemValues[itemId]++;
	}
	else
	{
		ItemValues.Add(itemId, 1);
	}
}