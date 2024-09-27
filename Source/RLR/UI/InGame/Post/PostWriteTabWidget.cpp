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
#include "GameManager/PostalManager.h"
#include "GameManager/GameManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostWriteTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* 버튼 바인딩 */
	if (SendPostButton)
		SendPostButton->OnClicked.AddDynamic(this, &UPostWriteTabWidget::OnSendPostButtonClicked);
	if (ClearPostButton)
		ClearPostButton->OnClicked.AddDynamic(this, &UPostWriteTabWidget::OnClearPostButtonClicked);
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
	TArray<FItemData> AttachedItems = GetAttachedItemsFromSlots();
	/*
		TODO : 이런식으로 SendPacket보내기, 그런데 PostId를 어떻게 설정해야하는지 모르겠음
		NetworkManager->SendPost(PostId, RecipientId, PostContentText.ToString(), AttachedItems, bIsSpecialPost);
	*/
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
	if (PostItemSlot)
		PostItemSlot->Clear();

	if(RecipientIdText)
		RecipientIdText->SetText(FText::GetEmpty());
	if(PostTitleText)
		PostTitleText->SetText(FText::GetEmpty());
}

TArray<FItemData> UPostWriteTabWidget::GetAttachedItemsFromSlots()
{
	TArray<FItemData> AttachedItems;

	// PostSlotList는 우편에 첨부된 아이템 슬롯 리스트
	for (UPostItemSlot* ItemSlot : PostSlotList)
	{
		if (IsValid(ItemSlot) && !ItemSlot->IsEmpty())
		{
			FItemData ItemData = ItemSlot->GetItemData();
			AttachedItems.Add(ItemData);
		}
	}

	return AttachedItems;
}

