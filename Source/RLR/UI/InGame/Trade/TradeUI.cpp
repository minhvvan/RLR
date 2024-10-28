// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeUI.h"
#include "UI/InGame/Trade/TradeList.h"
#include "UI/InGame/Trade/TradeListSlot.h"
#include "UI/InGame/Trade/TradeListElement.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/InGame/Popup/NotificationMessageBox.h"
#include "UI/BaseUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/ItemStructs.h"
#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UTradeUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTradeUI::Init()
{
	Super::Init();

	SetUIType(EUIType::TRADE_UI);
	SetUITag(FGameplayTagManager::Get().TradeUI);
	MyTradeList->Init();
	MyTradeList->SetCanDrag(true);
	TargetPlayerTradeList->Init();
	TargetPlayerTradeList->SetCanDrag(false);
	OfferButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendTradeLock);
	UnLockButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendTradeUnLock);
	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendTradeConfirm);
	AddGoldButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::OnClickedAddGoldButton);
}

void UTradeUI::RefreshUI()
{
	Super::RefreshUI();
	MyTradeList->RefreshUI();
	TargetPlayerTradeList->RefreshUI();
}

void UTradeUI::OpenUI()
{
	Super::OpenUI();
	Clear();

	/*
		개인 거래 UI가 열렸을 때, 인벤토리에서 아이템을 누르면 아이템 올라가게 이벤트를 추가해준다.
	*/
	GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("OnClickedInventorySlot"));
}

void UTradeUI::Clear()
{
	Super::Clear();
	MyTradeList->Clear();
	TargetPlayerTradeList->Clear();

	FText DefaultGold = STRING_TO_FTEXT("0");
	MyGoldText->SetText(DefaultGold);
	TargetGoldText->SetText(DefaultGold);

	SetMyTradeState(ETradeState::BEFORE_OFFER);
	SetTradeUnLock(true);
	SetTargetTradeState(ETradeState::BEFORE_OFFER);
	SetTradeUnLock(false);
}

void UTradeUI::CloseUI()
{
	Super::CloseUI();

	/*
	*	만약 거래 중인 상대가 존재한다면,
		개인 거래 UI를 닫을 때, 상대방한테 거래가 취소되었다는 메시지를 줘야 한다.
		
	*/
	SendTradeCancelPacket();
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
}

void UTradeUI::HandleTradeStartResponse(Protocol::SC_TradeStartResponse& pkt)
{
	AsyncTask(ENamedThreads::GameThread, [this, pkt]()
		{
			int32 MyUserSeq = pkt.userseq1();
			int32 TargetUserSeq = pkt.userseq2();

			FString MyUserName = UTF8_TO_TCHAR(pkt.username1().c_str());
			FString TargetUserName = UTF8_TO_TCHAR(pkt.username2().c_str());

			MyNameText->SetText(FText::FromString(MyUserName));
			TargetPlayerNameText->SetText(FText::FromString(TargetUserName));

			GetUIManager()->OpenUI(EUIType::TRADE_UI);
		});
}

void UTradeUI::SendTradeAddItemBySelf(const FItemData& NewTradeItem, int32 Quantity)
{
	GetNetworkManager()->SendTradeAddItemReqeust(NewTradeItem, Quantity);
}

void UTradeUI::SendTradeAddGoodBySelf(int32 Amount)
{
	GetNetworkManager()->SendTradeAddGoodReqeust(Amount);
}

void UTradeUI::SendTradeRemoveItemBySelf(const FItemData& NewTradeItem, int32 Quantity)
{
	GetNetworkManager()->SendRemoveTradeItem(NewTradeItem, Quantity);
}

void UTradeUI::HandleTradeAddItemByTarget(const FItemData& NewTradeItem)
{
	/*
		상대방이 아이템을 추가했다는 패킷 받았을 때 핸들. 
	*/
	AsyncTask(ENamedThreads::GameThread, [this, NewTradeItem]()
		{
			TargetPlayerTradeList->AddTradeItem(NewTradeItem);
		});
}

void UTradeUI::HandleTradeAddItemBySelf(const FItemData& NewTradeItem)
{
	/*
		내가 아이템을 추가했다는 패킷 받았을 때 핸들.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, NewTradeItem]()
		{
			MyTradeList->AddTradeItem(NewTradeItem);
		});
}

void UTradeUI::HandleTradeAddGoodBySelf(int32 Amount)
{
	AsyncTask(ENamedThreads::GameThread, [this, Amount]()
		{
			MyGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
		});
}

void UTradeUI::HandleTradeAddGoodByTarget(int32 Amount)
{
	AsyncTask(ENamedThreads::GameThread, [this, Amount]()
		{
			TargetGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
		});
}

void UTradeUI::HandleTradeRemoveItemByTarget(int32 ItemID)
{
	/*
		상대방이 아이템을 제거했다는 패킷 받았을 때 핸들.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, ItemID]()
		{
			TargetPlayerTradeList->RemoveTradeItem(ItemID);
		});
}

void UTradeUI::HandleTradeRemoveItemBySelf(int32 ItemID)
{
	/*
		내가 아이템을 제거했다는 패킷 받았을 때 핸들.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, ItemID]()
		{
			MyTradeList->RemoveTradeItem(ItemID);
		});
}

void UTradeUI::HandleTradeLockBySelf()
{
	/*
		내가 거래 잠금을 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeLock(true);
		});
}

void UTradeUI::HandleTradeUnLockBySelf()
{
	/*
		내가 거래 잠금 해제 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeUnLock(true);
		});
}

void UTradeUI::HandleTradeLockByTarget()
{
	/*
	*	상대방이 거래 잠금 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeLock(false);
		});
}

void UTradeUI::HandleTradeUnLockByTarget()
{
	/*
		상대방이 거래 잠금 해제 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeUnLock(false);
		});
}

void UTradeUI::HandleTradeWaitConfirm()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetMyTradeState(ETradeState::WAIT_CONFIRM_TRADE);
			TradeStateWidgetSwitcher->SetActiveWidgetIndex((uint32)ETradeState::WAIT_CONFIRM_TRADE);
		});
}

void UTradeUI::SendTradeLock()
{
	GetNetworkManager()->SendTradeLockRequest();
}

void UTradeUI::SendTradeUnLock()
{
	GetNetworkManager()->SendTradeUnlockReqeust();
}

void UTradeUI::SendTradeConfirm()
{
	GetNetworkManager()->SendTradeConfirmRequest();
}

void UTradeUI::SendTradeCancelPacket()
{
	/*
		상대방한테 거래가 취소되었다는 패킷을 보낸다.
	*/

	//거래가 이미 취소되거나 끝난 상태라면, 보내지 않는다.
	if(MyTradeState == ETradeState::CANCEL || MyTradeState == ETradeState::SUCCESS)
		return;

	GetNetworkManager()->SendTradeCancelReqeust();
}

void UTradeUI::HandleTradeCanceledByTarget()
{
	/*
		상대방이 거래를 취소 했을 때 받는 패킷 핸들.
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			//거래가 취소 되었다는 알림 UI를 띄운다.
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(EUIType::NOTIFICATION_MESSAGE_BOX);
			if (IsValid(NotificationMessageBox) == false)
				return;

			NotificationMessageBox->Clear();
			NotificationMessageBox->SetText(TEXT("상대가 거래를 취소했습니다"));
			SetMyTradeState(ETradeState::CANCEL);
			SetTargetTradeState(ETradeState::CANCEL);

			CloseUI();
		});
}

void UTradeUI::HandleTradeSuccess()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetMyTradeState(ETradeState::SUCCESS);
			SetTargetTradeState(ETradeState::SUCCESS);

			//거래가 성공했다는 알림을 띄운다.
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(EUIType::NOTIFICATION_MESSAGE_BOX);
			if (IsValid(NotificationMessageBox) == false)
				return;
			NotificationMessageBox->Clear();
			NotificationMessageBox->SetText(TEXT("상대가 거개를 취소했습니다"));

			CloseUI();
		});
}

void UTradeUI::SetTradeLock(bool IsSelf)
{
	if (IsSelf == true)
	{
		SetMyTradeState(ETradeState::LOCK);
		MyTradeList->SetCanDrag(false);
		MyTradeList->SetIsEnabled(false);
	}
	else if (IsSelf == false)
	{
		SetTargetTradeState(ETradeState::LOCK);
		TargetPlayerTradeList->SetIsEnabled(false);
	}
}

void UTradeUI::SetTradeUnLock(bool IsSelf)
{
	if (IsSelf == true)
	{
		SetMyTradeState(ETradeState::BEFORE_OFFER);
		MyTradeList->SetCanDrag(true);
		MyTradeList->SetIsEnabled(true);
	}
	else if (IsSelf == false)
	{
		SetTargetTradeState(ETradeState::BEFORE_OFFER);
		TargetPlayerTradeList->SetIsEnabled(true);
	}
}

void UTradeUI::OnClickedInventorySlot(const FItemData& NewTradeItem)
{
	//만약 Trade UI가 닫혀 있는 상태라면, 인벤토리 클릭 이벤트를 Clear 해준다.
	ESlateVisibility bOpened = GetVisibility();
	if (bOpened == ESlateVisibility::Hidden)
	{
		GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
		return;
	}
	

	/*
		아이템 갯수를 입력 받는 메시지 박스를 띄운다.
	*/
	UItemCountMessageBox* ItemCountMessageBox = OpenOtherUI<UItemCountMessageBox>(EUIType::ITEM_COUNT_MESSAGE_BOX);
	if (IsValid(ItemCountMessageBox) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	ItemCountMessageBox->Clear();
	ItemCountMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnConfirmItemCountMessageBox"));
	ItemCountMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnCancelItemCountMessageBox"));

	ItemCountMessageBox->SetItemData(NewTradeItem);
	ItemCountMessageBox->RefreshUI();
}

void UTradeUI::OnConfirmItemCountMessageBox(UItemCountMessageBox* MessageBox)
{
	/*
		확인 버튼 눌렀을 때 함수 진행.
	*/
	if(IsValid(MessageBox) == false)
		return;

	const FItemData& ItemData = MessageBox->GetItemData();
	int32 ItemCount = MessageBox->GetItemCount();

	//아무런 정보도 없으면 리턴
	if (ItemData == FItemData::EmptyItemData)
	{
		return;
	}

	// 아이템, 재화 분류
	if(ItemData.TYPE != EItemType::TotalMoney)
	{
		if (ItemCount < 1)
			ItemCount = 1;

		SendTradeAddItemBySelf(ItemData, ItemCount);
	}
	else if (ItemData.TYPE == EItemType::TotalMoney)
	{
		SendTradeAddGoodBySelf(ItemCount);
	}
}

void UTradeUI::OnCancelItemCountMessageBox(UItemCountMessageBox* MessageBox)
{
	/*
		취소했을 때 콜백 이벤트가 필요할지 모르겠지만 일단 남겨둔다.
	*/
}

void UTradeUI::OnClickedAddGoldButton()
{
	/*
		얼마나 입력할지 수량 입력 박스 띄우기
	*/
	UItemCountMessageBox* ItemCountMessageBox = OpenOtherUI<UItemCountMessageBox>(EUIType::ITEM_COUNT_MESSAGE_BOX);
	if (IsValid(ItemCountMessageBox) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	ItemCountMessageBox->Clear();
	ItemCountMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnConfirmItemCountMessageBox"));
	ItemCountMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnCancelItemCountMessageBox"));

	FItemData DummyData = FItemData(); 
	DummyData.ITEM_SEQ = (int32)EItemType::TotalMoney;
	DummyData.TYPE = EItemType::TotalMoney;
	DummyData.NAME = STRING_TO_FTEXT("골드");
	ItemCountMessageBox->SetItemData(DummyData);
	ItemCountMessageBox->RefreshUI();
}

void UTradeUI::SetMyTradeState(ETradeState TradeState)
{
	MyTradeState = TradeState;

	if (MyTradeState == ETradeState::WAIT_CONFIRM_TRADE)
	{
		OfferStateText->SetIsEnabled(false);
		TradeStateText->SetIsEnabled(true);
	}
	else
	{
		OfferStateText->SetIsEnabled(true);
		TradeStateText->SetIsEnabled(false);

		if(MyTradeState == ETradeState::BEFORE_OFFER || MyTradeState == ETradeState::LOCK)
			TradeStateWidgetSwitcher->SetActiveWidgetIndex((uint32)MyTradeState);
	}
}

void UTradeUI::SetTargetTradeState(ETradeState TradeType)
{
	TargetTradeState = TradeType;
}

