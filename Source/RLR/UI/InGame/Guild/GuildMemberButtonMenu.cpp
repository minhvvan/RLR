// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildMemberButtonMenu.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/PartyManager.h"

void UGuildMemberButtonMenu::NativeConstruct()
{
	if (PlayerInfoButton)
	{
		PlayerInfoButton->OnClicked.AddUniqueDynamic(this, &UGuildMemberButtonMenu::OpenPlayerInfoUI);
	}
	if (RemoveMemberButton)
	{
		RemoveMemberButton->OnClicked.AddUniqueDynamic(this, &UGuildMemberButtonMenu::RemoveMember);
	}
	if (InviteButton)
	{
		/* 파티 초대하기, 현재 파티에 추가하는 기능만 존재 */
		InviteButton->OnClicked.AddUniqueDynamic(this, &UGuildMemberButtonMenu::InviteParty);
	}
	if (WhisperChatButton)
	{
		/* 귓속말 */
		WhisperChatButton->OnClicked.AddUniqueDynamic(this, &UGuildMemberButtonMenu::OpenWhisperChat);
	}
	if (AddFriendButton)
	{
		AddFriendButton->OnClicked.AddUniqueDynamic(this, &UGuildMemberButtonMenu::RequestAddFriend);
	}
}

void UGuildMemberButtonMenu::OpenPlayerInfoUI()
{
	OnPlayerInfoClicked.Broadcast(currentGuildMember.UserSeq);
}

void UGuildMemberButtonMenu::RemoveMember()
{
	/* TODO : GameInstance->GetNetworkManager()->RemoveGuildMember()?? 하기 */
	int32 guildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	GameInstance->GetNetworkManager()->SendRemoveGuild(currentGuildMember.UserSeq, guildSeq);
}

void UGuildMemberButtonMenu::SetGuildMember(FGuildRank SelectedGuildMember)
{
	currentGuildMember = SelectedGuildMember;
}

void UGuildMemberButtonMenu::OpenWhisperChat()
{
	UChatUI* ChatUI = GameInstance->GetUIManager()->GetSubUI<UChatUI>(RLRTAG.UI_Chat);

	if (ChatUI)
	{
		ChatUI->OnTabClicked((int32)EChatType::Whisper);
		FString TargetUserName = currentGuildMember.UserName;
		ChatUI->AddWhisperChat(TargetUserName);
		ChatUI->SetCurrentChatTypeTab(EChatType::Whisper);
	}
}

void UGuildMemberButtonMenu::InviteParty()
{
	if (GameInstance->GetPartyManager()->GetHasParty())
	{
		GameInstance->GetPartyManager()->InviteParty(currentGuildMember.UserSeq);
	}
}

void UGuildMemberButtonMenu::RequestAddFriend()
{
	GameInstance->GetNetworkManager()->SendRequestFriend(currentGuildMember.UserName);
}

void UGuildMemberButtonMenu::SetPlayerNameText(FString CurrentGuildMemberName)
{
	PlayerNameText->SetText(FText::FromString(currentGuildMember.UserName));
}