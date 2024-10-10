// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/OtherUser/OtherPlayerMenu.h"
#include "Structs/UtilStructs.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/PartyManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/OtherUser/ReportUI.h"
#include "RLR.h"

void UOtherPlayerMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::OTHER_PLAYER_MENU);

	BtnUserInfo->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnUserInfoClicked);
	BtnAddFriend->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnAddFriendClicked);
	BtnAddParty->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnInvitePartyClicked);
	BtnTrade->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnTradeClicked);
	BtnWhisper->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnWhisperClicked);
	BtnReport->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnReportClicked);
	BtnCancel->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnCancelClicked);
}

void UOtherPlayerMenu::SetOtherUserData(TSharedPtr<FUserCharacter> Otheruser)
{
	OtherUserData = Otheruser;
}

void UOtherPlayerMenu::OnUserInfoClicked()
{
	auto TagManager = FGameplayTagManager::Get();
	auto subUI = GetUIManager()->GetSubUI(TagManager.UI_OtherPlayerStatus);
	auto otherPlayerStatus = Cast<UCharacterStatusUI>(subUI);

	if (!otherPlayerStatus || !OtherUserData.IsValid()) return;

	otherPlayerStatus->UpdateTotalStat(OtherUserData.Get()->TotalStatus);
	GetUIManager()->OpenSubUI(TagManager.UI_OtherPlayerStatus);
	CloseUIByManager();
}

void UOtherPlayerMenu::OnAddFriendClicked()
{
	if (!OtherUserData.IsValid()) return;
	GetNetworkManager()->SendAddFriend(OtherUserData->UserSeq);
	CloseUIByManager();
}

void UOtherPlayerMenu::OnInvitePartyClicked()
{
	auto partyManager = GetPartyManager();
	if (!partyManager) return;

	if (!partyManager->GetHasParty())
	{
		//Single 유지
		partyManager->SuccessCreate.Clear();
		partyManager->SuccessCreate.AddDynamic(this, &UOtherPlayerMenu::SuccessCreateParty);

		partyManager->CreateParty();
	}

	CloseUIByManager();
}

void UOtherPlayerMenu::OnTradeClicked()
{
	//TODO: 구체적인 구현 내용이 나오면 처리
	if (!OtherUserData.IsValid()) return;
	GetNetworkManager()->SendTradeStartRequest(OtherUserData->UserSeq);
	CloseUIByManager();
}

void UOtherPlayerMenu::OnWhisperClicked()
{
	auto TagManager = FGameplayTagManager::Get();
	auto chatUI = Cast<UChatUI>(GetUIManager()->GetSubUI(TagManager.UI_Chat));

	if (!chatUI || !OtherUserData.IsValid()) return;

	chatUI->AddWhisperChat(OtherUserData->NickName);
	CloseUIByManager();
}

void UOtherPlayerMenu::OnReportClicked()
{
	auto TagManager = FGameplayTagManager::Get();
	auto subUI = GetUIManager()->GetSubUI(TagManager.UI_Report);
	auto reportUI = Cast<UReportUI>(subUI);

	if (!reportUI || !OtherUserData.IsValid()) return;

	reportUI->SetUserName(OtherUserData->NickName);
	reportUI->SetUserSeq(OtherUserData->UserSeq);

	GetUIManager()->OpenSubUI(TagManager.UI_Report);

	CloseUIByManager();
}

void UOtherPlayerMenu::OnCancelClicked()
{
	CloseUIByManager();
}

void UOtherPlayerMenu::SuccessCreateParty()
{
	auto partyManager = GetPartyManager();
	if (!partyManager || !OtherUserData.IsValid()) return;

	partyManager->InviteParty(OtherUserData->UserSeq);
}