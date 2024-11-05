// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildManagementUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UGuildManagementUI::NativeConstruct()
{
	if (ChangeGuildNameButton)
	{
		ChangeGuildNameButton->OnClicked.AddDynamic(this, &UGuildManagementUI::ChangeNameButtonClicked);
	}
	if (InviteToGuildButton)
	{
		InviteToGuildButton->OnClicked.AddDynamic(this, &UGuildManagementUI::InviteButtonClicked);
	}
	if (QuitGuildButton)
	{
		QuitGuildButton->OnClicked.AddDynamic(this, &UGuildManagementUI::QuitGuldButtonClicked);
	}


	for (const FGuildRank& guildRank : GameInstance->GetGuildManager()->GetGuildInfo().GuildRanks)
	{
		if (guildRank.UserSeq == GameInstance->GetNetworkManager()->GetUserSeq())
		{
			/* 길드장에게만 보이도록 하기 */
			if (guildRank.GuildRankSeq == 4)
			{
				DeleteGuildButton->SetVisibility(ESlateVisibility::Visible);
				if (DeleteGuildButton)
				{
					DeleteGuildButton->OnClicked.AddDynamic(this, &UGuildManagementUI::DeleteGuildButtonClicked);
				}
			}
			else
			{
				DeleteGuildButton->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UGuildManagementUI::ChangeNameButtonClicked()
{
}

void UGuildManagementUI::InviteButtonClicked()
{
}

/* 길드 탈퇴 */
void UGuildManagementUI::QuitGuldButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	int32 UserSeq = GameInstance->GetNetworkManager()->GetUserSeq();
	GameInstance->GetNetworkManager()->SendRemoveGuild(UserSeq, GuildSeq);
}

/* 길드 삭제 */
void UGuildManagementUI::DeleteGuildButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	GameInstance->GetNetworkManager()->SendDeleteGuild(GuildSeq);
}
