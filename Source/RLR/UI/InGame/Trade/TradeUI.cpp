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
#include "GameManager/TradeManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"
#include "Structs/CommunicationStructs.h"

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

	SetUITag(FGameplayTagManager::Get().UI_Trade);
	MyTradeList->Init();
	MyTradeList->SetCanDrag(true);
	TargetPlayerTradeList->Init();
	TargetPlayerTradeList->SetCanDrag(false);
	OfferButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::SendTradeLock);
	AddGoldButton->OnClicked.AddUniqueDynamic(this, &UTradeUI::OnClickedAddGoldButton);
	
	UTradeManager* TradeManager = GetGameManager()->GetTradeManager();
	TradeManager->UpdateTradeManager.AddUniqueDynamic(this, &UTradeUI::RefreshUI);
}

void UTradeUI::RefreshUI()
{
	Super::RefreshUI();
	UpdateTradeData();
	UpdateTradeState();
}

void UTradeUI::OpenUI()
{
	Super::OpenUI();
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

	SetTradeUnLock(true);
	SetTradeUnLock(false);
}

void UTradeUI::CloseUI()
{
	Super::CloseUI();

	/*
	*	만약 거래 중인 상대가 존재한다면,
		개인 거래 UI를 닫을 때, 상대방한테 거래가 취소되었다는 메시지를 줘야 한다.
		
	*/
	const FTradeData& TradeState = GetGameManager()->GetTradeManager()->GetTradeData();
	if (TradeState.UserLockState1 == 1 && TradeState.UserLockState2 == 1)
	{
		//거래 성공. 
	}
	else
	{ 
		//거래 완료 전에 닫으면 거래 취소 패킷 보내기
		SendTradeCancelPacket();
	}
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
}

void UTradeUI::HandleTradeUserResponse(int32 UserSeq)
{
	/*
		거래 요청을 받았으면, 메시지 박스를 뛰운다.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, UserSeq]()
	{
		UConfirmMessageBox* ConfirmMessageBox = OpenOtherUI<UConfirmMessageBox>(FGameplayTagManager::Get().UI_Popup_ConfirmMessageBox);
		if (IsValid(ConfirmMessageBox) == false) return;
			
		ConfirmMessageBox->Clear();

		//클릭, 취소 버튼 콜백 함수 등록
		ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnClickedAcceptButton"));
		ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnClickedCancelButton"));

		ARLRPlayerCharacter* From = GameInstance->GetOtherUserManager()->GetPlayer(UserSeq);
		if(IsValid(From) == false)
			return;

		const UStatSetPlayer* FromStat =  From->GetStat();
		if(IsValid(FromStat) == false)
			return;

		//데이터 저장
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

void UTradeUI::HandleTradeStartResponse(int32 UserSeq1, FString UserName1, int32 UserSeq2, FString UserName2)
{
	AsyncTask(ENamedThreads::GameThread, [this, UserSeq1, UserName1, UserSeq2, UserName2]()
		{
			int32 MyUserSeq = GameInstance->GetUserSeq();

			if (MyUserSeq == UserSeq1)
			{
				MyNameText->SetText(FText::FromString(UserName1));
				TargetPlayerNameText->SetText(FText::FromString(UserName2));
			}
			else
			{
				MyNameText->SetText(FText::FromString(UserName2));
				TargetPlayerNameText->SetText(FText::FromString(UserName1));
			}

			Clear();
			GetUIManager()->OpenSubUI(FGameplayTagManager::Get().UI_Trade);
			GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("OnClickedInventorySlot"));
		});
}

void UTradeUI::UpdateTradeData()
{
	MyTradeList->Clear();
	TargetPlayerTradeList->Clear();

	const FTradeData& TradeState = GetGameManager()->GetTradeManager()->GetTradeData();

	if(TradeState.IsUserSeq1 == true)
	{
		//내가 UserSeq 1
		for (const FItemData& ItemData : TradeState.UserItemList1)
		{
			AddItemBySelf(ItemData);
		}
		AddGoodBySelf(TradeState.UserMoney1);

		if(TradeState.UserLockState1 == 1)
			LockBySelf();
		else
			UnLockBySelf();

		//상대가 UserSeq 2
		for (const FItemData& ItemData : TradeState.UserItemList2)
		{
			AddItemByTarget(ItemData);
		}
		AddGoodByTarget(TradeState.UserMoney2);

		if (TradeState.UserLockState2 == 1)
			LockByTarget();
		else
			UnLockByTarget();
	}
	else if(TradeState.IsUserSeq1 == false)
	{
		//내가 UserSeq 2
		for (const FItemData& ItemData : TradeState.UserItemList2)
		{
			AddItemBySelf(ItemData);
		}
		AddGoodBySelf(TradeState.UserMoney2);

		if (TradeState.UserLockState2 == 1)
			LockBySelf();
		else
			UnLockBySelf();

		//상대가 UserSeq 1
		for (const FItemData& ItemData : TradeState.UserItemList1)
		{
			AddItemByTarget(ItemData);
		}
		AddGoodByTarget(TradeState.UserMoney1);

		if (TradeState.UserLockState1 == 1)
			LockByTarget();
		else
			UnLockByTarget();
	}
}

void UTradeUI::UpdateTradeState()
{

	const FTradeData& TradeState = GetGameManager()->GetTradeManager()->GetTradeData();

	int32 LockState = 0;
	bool IsUserSeq1 = TradeState.IsUserSeq1;
	if(IsUserSeq1 == true)
		LockState = TradeState.UserLockState1;
	else
		LockState = TradeState.UserLockState2;

	if (LockState)
	{
		OfferStateText->SetIsEnabled(false);
		TradeStateText->SetIsEnabled(true);
	}
	else
	{
		OfferStateText->SetIsEnabled(true);
		TradeStateText->SetIsEnabled(false);		
	}
	TradeStateWidgetSwitcher->SetActiveWidgetIndex((uint32)LockState);
}

void UTradeUI::HandleTradeCompleteResponse()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			//거래가 성공했다는 알림을 띄운다.
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(RLRTAG.UI_Popup_NotificationMessageBox);
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

void UTradeUI::AddItemByTarget(const FItemData& NewTradeItem)
{
	/*
		상대방이 아이템을 추가했다는 패킷 받았을 때 핸들. 
	*/
	AsyncTask(ENamedThreads::GameThread, [this, NewTradeItem]()
		{
			TargetPlayerTradeList->AddTradeItem(NewTradeItem);
		});
}

void UTradeUI::AddItemBySelf(const FItemData& NewTradeItem)
{
	/*
		내가 아이템을 추가했다는 패킷 받았을 때 핸들.
	*/
	AsyncTask(ENamedThreads::GameThread, [this, NewTradeItem]()
		{
			MyTradeList->AddTradeItem(NewTradeItem);
		});
}

void UTradeUI::AddGoodBySelf(int32 Amount)
{
	AsyncTask(ENamedThreads::GameThread, [this, Amount]()
		{
			MyGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
		});
}

void UTradeUI::AddGoodByTarget(int32 Amount)
{
	AsyncTask(ENamedThreads::GameThread, [this, Amount]()
		{
			TargetGoldText->SetText(FText::FromString(FString::FromInt(Amount)));
		});
}

void UTradeUI::LockBySelf()
{
	/*
		내가 거래 잠금을 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeLock(true);
		});
}

void UTradeUI::UnLockBySelf()
{
	/*
		내가 거래 잠금 해제 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeUnLock(true);
		});
}

void UTradeUI::LockByTarget()
{
	/*
	*	상대방이 거래 잠금 했을 때 핸들
	*/
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			SetTradeLock(false);
		});
}

void UTradeUI::UnLockByTarget()
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

	const FTradeData& TradeData = GameInstance->GetTradeManager()->GetTradeData();
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
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(RLRTAG.UI_Popup_NotificationMessageBox);
			if(IsValid(NotificationMessageBox) == false)
				return;
			
			NotificationMessageBox->Clear();
			NotificationMessageBox->SetMessageText(TEXT("상대가 거래를 취소했습니다"));

			CloseUI();
		});
}

void UTradeUI::SetTradeLock(bool IsSelf)
{
	if (IsSelf == true)
	{
		MyTradeList->SetCanDrag(false);
		MyTradeList->SetIsEnabled(false);
	}
	else if (IsSelf == false)
	{
		TargetPlayerTradeList->SetIsEnabled(false);
	}
}

void UTradeUI::SetTradeUnLock(bool IsSelf)
{
	if (IsSelf == true)
	{
		MyTradeList->SetCanDrag(true);
		MyTradeList->SetIsEnabled(true);
	}
	else if (IsSelf == false)
	{
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
	UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(RLRTAG.UI_Popup_NotificationMessageBox);
	if (IsValid(NotificationMessageBox) == false) return;

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
	UItemCountMessageBox* ItemCountMessageBox = OpenOtherUI<UItemCountMessageBox>(RLRTAG.UI_Popup_ItemCountMessageBox);
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
	const FPlayerGoods& PlayerGoods = MessageBox->GetPlayerGoods();
	int32 TotalMoney = PlayerGoods.TotalMoney;

	//아무런 정보도 없으면 리턴
	if (ItemData == FItemData::EmptyItemData && PlayerGoods == FPlayerGoods::EmptyPlayerGoods)
	{
		return;
	}


	// 아이템 
	if (ItemData != FItemData::EmptyItemData)
	{
		if (ItemCount < 1)
			ItemCount = 1;

		//입력된 수량이 현재 내가 소유한 수량보다 많은지 클라이언트 단계에서 확인
		const FItemData& MyItemData = GetInventoryManager()->GetItem(ItemData.ITEM_ID);
		if (MyItemData == FItemData::EmptyItemData || ItemCount > MyItemData.ITEM_QUANTITY)
		{
			//보낼 수 없는 수량을 입력할 경우 경고 메시지
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(RLRTAG.UI_Popup_NotificationMessageBox);
			if (IsValid(NotificationMessageBox) == false)
				return;

			NotificationMessageBox->Clear();
			NotificationMessageBox->SetMessageText(TEXT("입력된 값이 현재 플레이어가 보유한 수량보다 많습니다"));
			return;
		}

		SendTradeAddItemBySelf(ItemData, ItemCount);
	}

	// 재화
	if (PlayerGoods != FPlayerGoods::EmptyPlayerGoods)
	{
		//입력된 수량이 현재 내가 소유한 수량보다 많은지 클라이언트 단계에서 확인
		const FPlayerGoods& MyPlayerGoods = GetPlayerManager()->GetPlayerGood();
		if (TotalMoney > MyPlayerGoods.TotalMoney)
		{
			//보낼 수 없는 수량을 입력할 경우 경고 메시지
			UNotificationMessageBox* NotificationMessageBox = OpenOtherUI<UNotificationMessageBox>(RLRTAG.UI_Popup_NotificationMessageBox);
			if (IsValid(NotificationMessageBox) == false)
				return;
			NotificationMessageBox->Clear();
			NotificationMessageBox->SetMessageText(TEXT("입력된 값이 현재 플레이어가 보유한 수량보다 많습니다"));
			return;
		}

		SendTradeAddGoodBySelf(TotalMoney);
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
	UItemCountMessageBox* ItemCountMessageBox = OpenOtherUI<UItemCountMessageBox>(RLRTAG.UI_Popup_ItemCountMessageBox);
	if (IsValid(ItemCountMessageBox) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	ItemCountMessageBox->Clear();
	ItemCountMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, FName("OnConfirmItemCountMessageBox"));
	ItemCountMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, FName("OnCancelItemCountMessageBox"));

	//UI 출력을 위한 더미 데이터.
	FItemData DummyData = FItemData(); 
	DummyData.ITEM_SEQ = -10;
	DummyData.TYPE = (int32)EItemType::NONE;
	DummyData.NAME = STRING_TO_FTEXT("골드");
	ItemCountMessageBox->SetItemData(DummyData);
	ItemCountMessageBox->RefreshUI();
}
