// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildReportAndExitUI.h"
#include "UI/InGame/Guild/PlayerGuildUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/MultiLineEditableText.h"

void UGuildReportAndExitUI::NativeConstruct()
{
	if (ReportTitleText)
	{
		ReportTitleText->OnTextChanged.AddUniqueDynamic(this, &UGuildReportAndExitUI::OnReportTitleChanged);
	}
	if (ReportContentText)
	{
		ReportContentText->OnTextChanged.AddUniqueDynamic(this, &UGuildReportAndExitUI::OnReportContentChanged);
	}
	if (ReportButton)
	{
		ReportButton->OnClicked.AddUniqueDynamic(this, &UGuildReportAndExitUI::OnReportButtonClicked);
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddUniqueDynamic(this, &UGuildReportAndExitUI::OnCloseButtonClicked);
	}
}

void UGuildReportAndExitUI::OnReportTitleChanged(const FText& Text)
{
	/* 글자 수 초과되면 잘라내기 */
	if (Text.ToString().Len() > TitleMaxCharacter)
	{
		ReportTitleText->SetText(FText::FromString(Text.ToString().Left(TitleMaxCharacter)));
	}
}

void UGuildReportAndExitUI::OnReportContentChanged(const FText& Text)
{
	/* 글자 수 초과되면 잘라내기 */
	if (Text.ToString().Len() > ContentMaxCharacter)
	{
		ReportTitleText->SetText(FText::FromString(Text.ToString().Left(ContentMaxCharacter)));
	}
}

void UGuildReportAndExitUI::OnReportButtonClicked()
{
	PlayerGuildUI->GuildReportAndExitUI->SetVisibility(ESlateVisibility::Hidden);
	PlayerGuildUI->SetGuildOpenState(false);
	/* TODO : SendReportAndExit() 생기면 그걸로 대체하기 */
	GameInstance->GetNetworkManager()->SendRemoveGuild(GameInstance->GetUserSeq(), GameInstance->GetGuildManager()->GetGuildInfo().guildSeq);
}

void UGuildReportAndExitUI::OnCloseButtonClicked()
{
	PlayerGuildUI->GuildReportAndExitUI->SetVisibility(ESlateVisibility::Hidden);
	PlayerGuildUI->SetGuildOpenState(false);
}