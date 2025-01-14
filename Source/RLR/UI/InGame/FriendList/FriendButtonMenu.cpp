// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "UI/InGame/OtherUser/PartyUI.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "Structs/UtilStructs.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PartyManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/FriendManager.h"

void UFriendButtonMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerInfoButton)
	{
		PlayerInfoButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::OpenFriendInfoUI);
	}
	if (RemoveFriendButton)
	{
		RemoveFriendButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::RemoveFriend);
	}
	if (MoveGroupButton)
	{
		MoveGroupButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::MoveGroup);
	}
	if (InviteButton)
	{
		/* 파티 초대하기, 현재 파티에 추가하는 기능만 존재 */
		InviteButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::InviteParty);
	}
	if (WhisperChatButton)
	{
		/* 귓속말 */
		WhisperChatButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::OpenWhisperChat);
	}
	if (TradeButton)
	{
		/* 교환 */
		TradeButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::SendTradeRequest);
	}
}

// TODO : 프로필 보기
void UFriendButtonMenu::OpenFriendInfoUI()
{
	OnFriendInfoClicked.Broadcast(friendSeq);
}
// 친구 삭제
void UFriendButtonMenu::RemoveFriend()
{
	GameInstance->GetNetworkManager()->SendRemoveFriend(friendSeq);
	GameInstance->GetFriendManager()->FriendListUI->OpenFriendMenuUI(true);
}
// 그룹 이동(그룹 리스트 Open)
void UFriendButtonMenu::MoveGroup()
{
	OnMoveGroupClicked.Broadcast();
}

void UFriendButtonMenu::OpenWhisperChat()
{
	UChatUI* ChatUI = GameInstance->GetUIManager()->GetSubUI<UChatUI>(RLRTAG.UI_Chat);
	
	if (ChatUI)
	{
		ChatUI->OnTabClicked((int32)EChatType::Whisper);
		FString TargetUserName = friendName;
		ChatUI->AddWhisperChat(TargetUserName);
		ChatUI->SetCurrentChatTypeTab(EChatType::Whisper);
	}
}

void UFriendButtonMenu::SendTradeRequest()
{
	/* 상대에게 거래 요청 패킷 전송 */
	GameInstance->GetNetworkManager()->SendTradeUserRequest(friendSeq);
}

void UFriendButtonMenu::InviteParty()
{
	if (GameInstance->GetPartyManager()->GetHasParty())
	{
		GameInstance->GetPartyManager()->InviteParty(friendSeq);
	}
}

void UFriendButtonMenu::SetPlayerNameText(FString CurrentFriendName)
{
	PlayerNameText->SetText(FText::FromString(CurrentFriendName));
}