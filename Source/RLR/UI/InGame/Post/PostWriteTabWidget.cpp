// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostWriteTabWidget.h"
#include "UI/InGame/Post/PostBundleSend.h"
#include "UI/InGame/Post/InputTransactionCost.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"

#include "Components/MultiLineEditableText.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"

#include "GameManager/NetworkManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

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

void UPostWriteTabWidget::AddItemToPostSlot(const FItemData& ItemData, int32 InventorySlotIndex)
{
	
	UPostItemSlot* entry = GetItemSlotWidget(GetAttachedItemsFromSlots().Num());
	if (entry == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("entry is nullptr"));
		return;
	}
	UTexture2D* itemTexture = GameInstance->GetInventoryManager()->GetInventorySlot(InventorySlotIndex)->GetItemResourceData().ItemImage;

	entry->SetItemData(ItemData);
	entry->SetSlotImage(itemTexture);
	entry->SetItemAmountShow(true);
	entry->SetInventorySlotIndex(InventorySlotIndex);

	UInventoryUI* Inventory = GameInstance->GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if(!Inventory) return;
	
	Inventory->SelectSlot(InventorySlotIndex);

	//UpdatePage();
}

void UPostWriteTabWidget::OpenBundleItemSend(const FItemData& ItemData, int32 InventorySlotIndex)
{
	if(!GameInstance->GetPostalManager()->PostUIClass->CanSendItem()) return;

	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto bundleSendClass = dataManager->GetWidgetClass<UPostBundleSend>(RLRLITERAL.WBP_PostBundleSend);
	if (!bundleSendClass) return;

	auto bundleUI = CreateWidget<UPostBundleSend>(GetWorld(), bundleSendClass);
	bundleUI->SetSlotIndex(InventorySlotIndex);
	bundleUI->SetItemData(ItemData);
	bundleUI->ConfirmSendPostBundle.AddUniqueDynamic(this, &UPostWriteTabWidget::AddItemToPostSlot);

	auto postUI = GameInstance->GetUIManager()->GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if (!postUI) return;

	auto slot = Cast<UCanvasPanelSlot>(postUI->AddChild(bundleUI));
	FVector2D panelSize(postUI->RootSizeBox->WidthOverride, postUI->RootSizeBox->HeightOverride);
	slot->SetSize(panelSize);
}

UPostItemSlot* UPostWriteTabWidget::GetItemSlotWidget(int32 idx)
{
	if(!PostSlotGridPanel || idx >= PostSlotGridPanel->GetChildrenCount()) return nullptr;
	UWidget* Widget = PostSlotGridPanel->GetChildAt(idx);
	return Cast<UPostItemSlot>(Widget);
}

void UPostWriteTabWidget::AddEmptySlotsToGridPanel()
{
	if(!PostSlotGridPanel) return;
	
	const int32 MaxSlots = 10;
	UDataManager* DataManager = GameInstance->GetDataManager();
	if(!DataManager) return;

	TSubclassOf<UPostItemSlot> PostItemSlotClass = DataManager->GetWidgetClass<UPostItemSlot>(RLRLITERAL.WBP_PostItemSlot);
	if(!PostItemSlotClass) return;

	for (int32 i = 0; i < MaxSlots; i++)
	{
		UPostItemSlot* NewSlot = CreateWidget<UPostItemSlot>(GetWorld(), PostItemSlotClass);
		if (NewSlot)
		{
			NewSlot->SetItemData(FItemData::EmptyItemData);
			PostSlotGridPanel->AddChildToGrid(NewSlot, i/5, i%5);
		}
	}
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

	UInventoryUI* Inventory = GameInstance->GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (!Inventory) return;

	// PostItemSlot 초기화
	if (PostSlotGridPanel)
	{
		for (UWidget* Widget : PostSlotGridPanel->GetAllChildren())
		{
			if (UPostItemSlot* itemSlot = Cast<UPostItemSlot>(Widget))
			{
				Inventory->CancelSelectSlot(itemSlot->GetInventorySlotIndex());
			}
		}
		PostSlotGridPanel->ClearChildren();
		AddEmptySlotsToGridPanel();
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

void UPostWriteTabWidget::UpdatePage()
{
	if (!PostSlotGridPanel)
	{
		RLR_LOG(LogRLR, Warning, TEXT("PostSlotGridPanel is null"));
		return;
	}

	// 먼저 기존의 모든 슬롯 초기화
	for (UWidget* Child : PostSlotGridPanel->GetAllChildren())
	{
		if (UPostItemSlot* ItemSlot = Cast<UPostItemSlot>(Child))
		{
			ItemSlot->Clear();
		}
	}

	// 첨부된 아이템 불러오기
	TArray<int64> AttachedItems = GetAttachedItemsFromSlots();

	// 아이템 데이터를 UI에 표시
	for (int32 i = 0; i < AttachedItems.Num(); ++i)
	{
		UPostItemSlot* ItemSlot = GetItemSlotWidget(i);
		if (ItemSlot)
		{
			FItemData ItemData = GameInstance->GetPostalManager()->GetItemDataById(AttachedItems[i]);
			ItemSlot->SetItemData(ItemData);
			ItemSlot->SetItemAmountShow(ItemData.ITEM_QUANTITY > 1);
		}
	}

	// 남은 슬롯에 빈 아이템 데이터 설정 (최대 슬롯 수 유지)
	const int32 MaxSlots = 12;  // 최대 첨부 가능한 아이템 수
	for (int32 i = AttachedItems.Num(); i < MaxSlots; ++i)
	{
		UPostItemSlot* ItemSlot = GetItemSlotWidget(i);
		if (ItemSlot)
		{
			ItemSlot->SetItemData(FItemData::EmptyItemData);
			ItemSlot->SetItemAmountShow(false);
		}
	}
}