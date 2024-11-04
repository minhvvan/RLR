// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Structs/UtilStructs.h"

void UGuildUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::Guild);
	SetUITag(FGameplayTagManager::Get().Action_Default_GuildOpen);
}

void UGuildUI::Init()
{
}

void UGuildUI::RefreshUI()
{
	/* Set GuildManager */
	GameInstance->GetGuildManager()->InitializeGuildManager();
	if (GameInstance->GetGuildManager()->GetGuildValidation())
	{
		GameInstance->GetNetworkManager()->SendInfoGuild();
	}
	else
	{
		if (WidgetSwitcher)
		{
			WidgetSwitcher->SetActiveWidgetIndex(0);
		}
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
