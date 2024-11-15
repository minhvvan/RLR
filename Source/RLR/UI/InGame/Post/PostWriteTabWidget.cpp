// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "Components/MultiLineEditableText.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/GameManager.h"
#include "Structs/UtilStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostWriteTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* 버튼 바인딩 */
	if (SendPostButton)
		SendPostButton->OnClicked.AddUniqueDynamic(this, &UPostWriteTabWidget::OnSendPostButtonClicked);
	if (ClearPostButton)
		ClearPostButton->OnClicked.AddUniqueDynamic(this, &UPostWriteTabWidget::OnClearPostButtonClicked);
}

void UPostWriteTabWidget::OnNormalPostButtonClicked()
{
}

void UPostWriteTabWidget::OnSpecialPostButtonClicked()
{
}

void UPostWriteTabWidget::AddItemToPostSlot(const FItemData& ItemData)
{
}

void UPostWriteTabWidget::OnSendPostButtonClicked()
{
	FString RecipientIdString = RecipientIdText->GetText().ToString();

	if(RecipientIdText == nullptr) return;	

	FPostResult PostResult;
	{	
		/* 임시 값 */
		PostResult.ReceiverName = RecipientIdString;
		PostResult.PostId = GameInstance->GetPostalManager()->GetReceivedPostData().Num() + 1;
		PostResult.SenderSeq = GameInstance->GetUserSeq();
		PostResult.ItemId = GetAttachedItemsFromSlots();
		PostResult.ItemValues = GameInstance->GetPostalManager()->ItemValues;
		PostResult.Title = PostTitleText->GetText().ToString();
		PostResult.Content = PostContentText->GetText().ToString();
		PostResult.TotalMoney = FCString::Atoi(*GrantCostInput->TransactionCostInput->GetText().ToString());
	}

	GameInstance->GetNetworkManager()->SendPostRequest(PostResult);
	GameInstance->GetNetworkManager()->SendPostGetRequest();

	OnClearPostButtonClicked();

	for (int i = 0; i < PostResult.ItemId.Num(); i++)
	{
		// 인벤토리에서 첨부한 아이템들 제거
		GameInstance->GetInventoryManager()->RemoveItem(PostResult.ItemId[i]);
	}
}

void UPostWriteTabWidget::OnClearPostButtonClicked()
{
	// 입력 필드 초기화
	RequestCostInput->TransactionCostInput->SetText(FText::GetEmpty());
	GrantCostInput->TransactionCostInput->SetText(FText::GetEmpty());

	// PostContentText 초기화
	if (PostContentText)
		PostContentText->SetText(FText::GetEmpty());

	// PostItemSlot 초기화
	for (UWidget* Child : PostSlotGridPanel->GetAllChildren())
	{
		if (UPostItemSlot* itemSlot = Cast<UPostItemSlot>(Child))
		{
			itemSlot->Clear();
		}
	}

	if(RecipientIdText)
		RecipientIdText->SetText(FText::GetEmpty());

	if(PostTitleText)
		PostTitleText->SetText(FText::GetEmpty());
}

TArray<int64> UPostWriteTabWidget::GetAttachedItemsFromSlots()
{
	TArray<int64> AttachedItems;

	// PostSlotList는 우편에 첨부된 아이템 슬롯 리스트
	for (UWidget* Child : PostSlotGridPanel->GetAllChildren())
	{
		if (UPostItemSlot* itemSlot = Cast<UPostItemSlot>(Child))
		{
			if (IsValid(itemSlot) && !itemSlot->IsEmpty())
			{
				FItemData ItemData = itemSlot->GetItemData();
				GameInstance->GetPostalManager()->SetItemData(ItemData.ITEM_ID);
				AttachedItems.Add(ItemData.ITEM_ID);
			}
		}
	}

	return AttachedItems;
}

