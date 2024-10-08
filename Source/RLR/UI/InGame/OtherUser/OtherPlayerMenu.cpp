// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/OtherUser/OtherPlayerMenu.h"
#include "Structs/UtilStructs.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/OtherUser/ReportUI.h"
#include "RLR.h"

void UOtherPlayerMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::OTHER_PLAYER_MENU);

	BtnUserInfo->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnUserInfoClicked);
	BtnAddFriend->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnAddFriendClicked);
	BtnAddParty->OnClicked.AddDynamic(this, &UOtherPlayerMenu::OnAddPartyClicked);
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
	//TODO: Send Pkt
	if (!OtherUserData.IsValid()) return;
	GetNetworkManager()->SendAddFriend(OtherUserData->UserSeq);
	CloseUIByManager();
}

void UOtherPlayerMenu::OnAddPartyClicked()
{
	//TODO: Send Pkt
	//파티 시스템에따라 달라질듯
	CloseUIByManager();
}

void UOtherPlayerMenu::OnTradeClicked()
{
	//TODO: Show Trade UI & Send Pkt
	CloseUIByManager();
}

void UOtherPlayerMenu::OnWhisperClicked()
{
	//TODO: 채팅 대상 변경
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