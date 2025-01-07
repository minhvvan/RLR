// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildMember/GuildMemberUI.h"
#include "UI/InGame/Guild/GuildMemberButtonMenu.h"
#include "UI/InGame/Guild/GuildMember.h"

#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

void UGuildMemberUI::NativeConstruct()
{
}

void UGuildMemberUI::UpdateGuildMemberUI(FGuildResult NewGuildData)
{
	guildMembers.Empty();

	for (int32 i = 0; i < NewGuildData.GuildRanks.Num(); i++)
	{
		AddGuildMembers(NewGuildData.GuildRanks[i]);
	}
}

TArray<TObjectPtr<UGuildMember>> UGuildMemberUI::GetGuildMembers()
{
	return guildMembers;
}

void UGuildMemberUI::AddGuildMembers(FGuildRank NewGuildMember)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewGuildMember]()
		{
			UGuildMember* GuildMember = CreateWidget<UGuildMember>(this, GuildMemberClass);
			GuildMember->SetGuildMember(NewGuildMember);
			GuildMember->OnGuildMemberRightClicked.AddUniqueDynamic(this, &UGuildMemberUI::OnGuildMemberRightClicked);
			GuildMemberScrollBox->AddChild(GuildMember);
			guildMembers.Add(GuildMember);
		});
}

void UGuildMemberUI::OnGuildMemberRightClicked(FVector2D AbsolutePosition, UBaseGuildMember* GuildMemberButtonUI)
{
	if(!GuildMemberButtonMenu || !GuildMemberButtonUI) return;

	/* 추방하기 버튼은 길드장에게만 보임 */
	if (selectedGuildMember.GuildRankSeq != EGuildRole::MASTER)
	{
		GuildMemberButtonMenu->RemoveMemberButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		GuildMemberButtonMenu->RemoveMemberButton->SetVisibility(ESlateVisibility::Visible);
	}

	selectedGuildMember = GuildMemberButtonUI->GetGuildMember();

	/*FVector2D RelativePosition = GetCachedGeometry().AbsoluteToLocal(
		GuildMemberButtonUI->GetCachedGeometry().LocalToAbsolute(FVector2D::Zero())
	);*/
	if (bIsGuildMemberMenuOpen)
	{
		bIsGuildMemberMenuOpen = false;

		GuildMemberButtonMenu->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bIsGuildMemberMenuOpen = true;

		// GuildMemberButtonMenu의 위치를 버튼의 로컬 마우스 위치 기준으로 설정
		FVector2D MenuPosition = GuildMemberButtonUI->GetCachedGeometry().LocalToAbsolute(AbsolutePosition);
		FVector2D RelativeMenuPosition = GetCachedGeometry().AbsoluteToLocal(MenuPosition);

		// RenderTransform으로 위치 설정
		FWidgetTransform NewTransform;
		NewTransform.Translation = RelativeMenuPosition;
		GuildMemberButtonMenu->SetRenderTransform(NewTransform);

		GuildMemberButtonMenu->SetVisibility(ESlateVisibility::Visible);
		GuildMemberButtonMenu->SetGuildMember(selectedGuildMember);
		GuildMemberButtonMenu->SetPlayerNameText(selectedGuildMember.UserName);
	}
}