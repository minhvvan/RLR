// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameplayTagManager.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Structs/UtilStructs.h"


void UGuildUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(RLRTAG.Action_Default_GuildOpen);
	GameInstance->GetGuildManager()->GuildOverlayUI = this;
  
}

void UGuildUI::Init()
{
}

void UGuildUI::RefreshUI()
{
	if (GameInstance->GetGuildManager()->GetGuildInfo().guildSeq == 0)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		GameInstance->GetNetworkManager()->SendInfoGuild();
	}
}

FReply UGuildUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsInUI(InGeometry, InMouseEvent))
	{
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

bool UGuildUI::IsInUI(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	return InGeometry.IsUnderLocation(InMouseEvent.GetScreenSpacePosition());
}
