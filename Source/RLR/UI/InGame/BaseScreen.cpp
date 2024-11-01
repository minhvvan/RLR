// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/BaseScreen.h"
#include "UI/DialogueUI.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Components/PageSwitcher.h"
#include "GameManager/GameplayTagManager.h"

void UBaseScreen::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i = 0 ; i < PageSwitcher->GetChildrenCount(); i++)
	{
		auto page = Cast<UBaseUI>(PageSwitcher->GetChildAt(i));
		if (!page) continue;

		if (i == 0) ActivePageTag = page->UITag;
		PageIndices.Add(page->UITag, i);
	}
}

UWidget* UBaseScreen::GetPage(FGameplayTag tag)
{
	if (!PageIndices.Contains(tag)) return nullptr;
	return PageSwitcher->GetWidgetAtIndex(PageIndices[tag]);
}

UWidget* UBaseScreen::GetActivePage()
{
	return GetPage(ActivePageTag);
}

FGameplayTag UBaseScreen::GetActivePageTag()
{
	return ActivePageTag;
}

void UBaseScreen::SetActivePage(FGameplayTag tag)
{
	if (!PageIndices.Contains(tag)) return;
	PageSwitcher->SetActiveWidgetIndex(PageIndices[tag]);
	ActivePageTag = tag;

	auto activeWidget = Cast<UMainUI>(GetActivePage());
	if (!activeWidget) return;

	activeWidget->OnPageActivated();
}

bool UBaseScreen::SetPageUI(FGameplayTag tag, TObjectPtr<UBaseUI> newPage)
{
	if (!PageIndices.Contains(tag)) return false;

	PageSwitcher->SetWidgetAtIndex(PageIndices[tag], newPage);
	return true;
}

void UBaseScreen::AddPageUI(FGameplayTag tag, TObjectPtr<UBaseUI> newPage)
{
	if (PageIndices.Contains(tag)) return;

	PageIndices.Add(tag, PageIndices.Num());
	PageSwitcher->AddChild(newPage);
}
