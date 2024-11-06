// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "Components/MultiLineEditableText.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "GameManager/NetworkManager.h"
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
	/* userName을 통해 userSeq를 가져올 수 있는지 확인하고, 그렇게 변경하기 */
	/*
	*	ue5에서 사용자 이름 가져오는 방법 1. 
		if (GEngine && GEngine->GetFirstLocalPlayerController(GetWorld()))
		{
			APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
			if (PlayerController)
			{
				APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>();
				if (PlayerState)
				{
					FString PlayerName = PlayerState->GetPlayerName();
					UE_LOG(LogTemp, Log, TEXT("Local Player Name: %s"), *PlayerName);
				}
			}
		}
	
	*/
	FString RecipientIdString = RecipientIdText->GetText().ToString();

	if(RecipientIdText == nullptr) return;	

	FPostResult PostResult;
	{	
		/* 임시 값 */
		PostResult.ReceiverName = RecipientIdString;
		PostResult.PostId = GameInstance->GetPostalManager()->GetReceivedPostData().Num() + 1;
		PostResult.SenderSeq = GameInstance->GetNetworkManager()->GetUserSeq();
		PostResult.ItemId = GetAttachedItemsFromSlots();
		PostResult.Title = PostTitleText->GetText().ToString();
		PostResult.Content = PostContentText->GetText().ToString();
		PostResult.TotalMoney = FCString::Atoi(*GrantCostInput->TransactionCostInput->GetText().ToString());
	}

	GameInstance->GetNetworkManager()->SendPostRequest(PostResult);
	GameInstance->GetNetworkManager()->SendPostGetRequest();
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

TArray<int64> UPostWriteTabWidget::GetAttachedItemsFromSlots()
{
	TArray<int64> AttachedItems;

	// PostSlotList는 우편에 첨부된 아이템 슬롯 리스트
	for (UPostItemSlot* ItemSlot : PostSlotList)
	{
		if (IsValid(ItemSlot) && !ItemSlot->IsEmpty())
		{
			FItemData ItemData = ItemSlot->GetItemData();
			GameInstance->GetPostalManager()->SetItemData(ItemData.ITEM_ID);
			AttachedItems.Add(ItemData.ITEM_ID);
		}
	}
	return AttachedItems;
}

