// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Structs/UtilStructs.h"

void UGuildUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::Guild);
	SetUITag(FGameplayTagManager::Get().Action_Default_GuildOpen);

	if (CreateGuildButton)
	{
		CreateGuildButton->OnClicked.AddDynamic(this, &UGuildUI::OpenCreateGuildUI);
	}
	if (ApplyGuildButton)
	{
		ApplyGuildButton->OnClicked.AddDynamic(this, &UGuildUI::OpenApplyGuildUI);
	}
}

void UGuildUI::Init()
{
}

void UGuildUI::RefreshUI()
{
	/* GuildManager 으로부터 정보를 받아온다 */
	GameInstance->GetGuildManager()->InitializeGuildManager();
}

void UGuildUI::OpenApplyGuildUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UGuildUI::OpenCreateGuildUI()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
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
