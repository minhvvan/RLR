// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildManagement/GuildManagementUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UGuildManagementUI::NativeConstruct()
{
	if (ChangeGuildNameButton)
	{
		ChangeGuildNameButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::ChangeNameButtonClicked);
	}
	if (QuitGuildButton)
	{
		QuitGuildButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::QuitGuldButtonClicked);
	}


	for (const FGuildRank& guildRank : GameInstance->GetGuildManager()->GetGuildInfo().GuildRanks)
	{
		if (guildRank.UserSeq == GameInstance->GetUserSeq())
		{
			/* 길드장에게만 보이도록 하기 */
			if (guildRank.GuildRankSeq == EGuildRole::MASTER)
			{
				DeleteGuildButton->SetVisibility(ESlateVisibility::Visible);
				if (DeleteGuildButton)
				{
					DeleteGuildButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::DeleteGuildButtonClicked);
				}
			}
			else
			{
				DeleteGuildButton->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		break;
	}
}

void UGuildManagementUI::ChangeNameButtonClicked()
{
}

/* 길드 탈퇴 */
void UGuildManagementUI::QuitGuldButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	int32 UserSeq = GameInstance->GetUserSeq();
	GameInstance->GetNetworkManager()->SendRemoveGuild(UserSeq, GuildSeq);
}

/* 길드 삭제 */
void UGuildManagementUI::DeleteGuildButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	GameInstance->GetNetworkManager()->SendDeleteGuild(GuildSeq);
}
