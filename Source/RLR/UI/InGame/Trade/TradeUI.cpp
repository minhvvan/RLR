// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeUI.h"
#include "UI/InGame/Trade/TradeList.h"
#include "UI/InGame/Trade/TradeListSlot.h"
#include "UI/InGame/Trade/TradeListElement.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "UI/InGame/Popup/NotificationMessageBox.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"
#include "UI/BaseUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/OtherUserManager.h"
#include "GameManager/PlayerManager.h"

#include "Structs/ItemStructs.h"
#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"

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
	//UnLockButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendTradeUnLock);
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

void UTradeUI::HandleTradeUserResponse(Protocol::SC_TradeUserResponse& pkt)
{
	/*
		거래 요청을 받았으면, 메시지 박스를 뛰운다.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, pkt]()
	{
		UConfirmMessageBox* ConfirmMessageBox = OpenOtherUI<UConfirmMessageBox>(EUIType::CONFIRM_MESSAGE_BOX);
		if (IsValid(ConfirmMessageBox) == false)
			return;
		ConfirmMessageBox->Clear();
		ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnClickedAcceptButton"));
		ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnClickedCancelButton"));

		ARLRPlayerCharacter* From = GameInstance->GetOtherUserManager()->GetPlayer(pkt.userseq());
		if(IsValid(From) == false)
			return;

		const UStatSetPlayer* FromStat =  From->GetStat();
		if(IsValid(FromStat) == false)
			return;

		FEtcPropertyData FromData;
		FromData.EtcStringMap.Add("NickName", FromStat->GetNickName());
		FromData.EtcIntMap.Add("UserSeq", FromStat->GetUserSeq());
		ConfirmMessageBox->EtcPropertyMap.Add("From", FromData);

		FString NickName = FromStat->GetNickName();
		FText Text1 = STRING_TO_FTEXT("가 거래를 신청했습니다");
		FText MessageTextFormat = FText::Format(
			FText::FromString(TEXT("[{0}]{1}")),
			FText::FromString(NickName),
			Text1
		);
		ConfirmMessageBox->SetMessageText(MessageTextFormat);
	});
}

void UTradeUI::HandleTradeStartResponse(Protocol::SC_TradeStartResponse& pkt)
{
	AsyncTask(ENamedThreads::GameThread, [this, pkt]()
		{
			int32 UserSeq1 = pkt.userseq1();
			int32 UserSeq2 = pkt.userseq2();

			FString UserName1 = UTF8_TO_TCHAR(pkt.username1().c_str());
			FString UserName2 = UTF8_TO_TCHAR(pkt.username2().c_str());

			int32 MyUserSeq = GameInstance->GetPlayerManager()->GetUserSeq();

			if (MyUserSeq == UserSeq1)
			{
				IsUserSeq1 = true;
				MyNameText->SetText(FText::FromString(UserName1));
				TargetPlayerNameText->SetText(FText::FromString(UserName2));
			}
			else
			{
				IsUserSeq1 = false;
				MyNameText->SetText(FText::FromString(UserName2));
				TargetPlayerNameText->SetText(FText::FromString(UserName1));
			}

			GetUIManager()->OpenUI(EUIType::TRADE_UI);
		});
}

void UTradeUI::HandleTradeStateResponse(Protocol::SC_TradeStateResponse& pkt)
{
	AsyncTask(ENamedThreads::GameThread, [this, pkt]()
	{
		MyTradeList->Clear();
		TargetPlayerTradeList->Clear();

		TArray<FItemData> UserItemList1;
		for (int32 i = 0; i < pkt.useritemlist1_size(); i++) {
			FItemData itemData;
			itemData.MakeItemData(pkt.useritemlist1().at(i));
			UserItemList1.Add(itemData);
		}
		int32 UserMoney1 = pkt.totalmoney1();
		int32 UserLockState1 = pkt.lockstate1();

		TArray<FItemData> UserItemList2;
		for (int32 i = 0; i < pkt.useritemlist2_size(); i++) {
			FItemData itemData;
			itemData.MakeItemData(pkt.useritemlist2().at(i));
			UserItemList2.Add(itemData);
		}
		int32 UserMoney2 = pkt.totalmoney2();
		int32 UserLockState2 = pkt.lockstate2();

		if(IsUserSeq1 == true)
		{
			//내가 UserSeq 1
			for (const FItemData& ItemData : UserItemList1)
			{
				HandleTradeAddItemBySelf(ItemData);
			}
			HandleTradeAddGoodBySelf(UserMoney1);

			if(UserLockState1 == 1)
				HandleTradeLockBySelf();
			else
				HandleTradeUnLockBySelf();

			//상대가 UserSeq 2
			for (const FItemData& ItemData : UserItemList2)
			{
				HandleTradeAddItemByTarget(ItemData);
			}
			HandleTradeAddGoodByTarget(UserMoney2);

			if (UserLockState2 == 1)
				HandleTradeLockByTarget();
			else
				HandleTradeUnLockByTarget();
		}
		else if(IsUserSeq1 == false)
		{
			//내가 UserSeq 2
			for (const FItemData& ItemData : UserItemList2)
			{
				HandleTradeAddItemBySelf(ItemData);
			}
			HandleTradeAddGoodBySelf(UserMoney2);

			if (UserLockState2 == 1)
				HandleTradeLockBySelf();
			else
				HandleTradeUnLockBySelf();

			//상대가 UserSeq 1
			for (const FItemData& ItemData : UserItemList1)
			{
				HandleTradeAddItemByTarget(ItemData);
			}
			HandleTradeAddGoodByTarget(UserMoney1);

			if (UserLockState1 == 1)
				HandleTradeLockByTarget();
			else
				HandleTradeUnLockByTarget();
		}
	});
}

void UTradeUI::HandleTradeCompleteResponse(Protocol::SC_TradeCompleteResponse& pkt)
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
			NotificationMessageBox->SetMessageText(TEXT("거래를 성공했습니다"));

			CloseUI();
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

void UTradeUI::SendTradeLock()
{
	GetNetworkManager()->SendTradeLockRequest();
}

void UTradeUI::SendTradeUnLock()
{
	//GetNetworkManager()->SendTradeUnlockReqeust();
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
			NotificationMessageBox->SetMessageText(TEXT("상대가 거래를 취소했습니다"));
			SetMyTradeState(ETradeState::CANCEL);
			SetTargetTradeState(ETradeState::CANCEL);

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

void UTradeUI::OnClickedAcceptButton(UConfirmMessageBox* MessageBox)
{
	FEtcPropertyData* FromData = MessageBox->EtcPropertyMap.Find("From");
	if(FromData == nullptr)
		return;
	int32* FromUserSeq = FromData->EtcIntMap.Find("UserSeq");
	if(FromUserSeq == nullptr)
		return;
	GetNetworkManager()->SendTradeStartReqeust(*FromUserSeq);
}

void UTradeUI::OnClickedCancelButton(UConfirmMessageBox* MessageBox)
{
	UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(EUIType::NOTIFICATION_MESSAGE_BOX);
	if (IsValid(NotificationMessageBox) == false)
		return;
	NotificationMessageBox->Clear();

	FEtcPropertyData* FromData = MessageBox->EtcPropertyMap.Find("From");
	if (FromData == nullptr)
		return;
	FString FromNickName = FromData->EtcStringMap["NickName"];
	if (FromNickName.IsEmpty())
		return;
	FText Text1 = STRING_TO_FTEXT("거래를 거절했습니다");
	FText MessageTextFormat = FText::Format(
		FText::FromString(TEXT("[{0}] {1}")),
		FText::FromString(FromNickName),
		Text1
	); 
	NotificationMessageBox->SetMessageText(MessageTextFormat);
	CloseUI();
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

