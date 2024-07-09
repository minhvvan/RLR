// Fill out your copyright notice in the Description page of Project Settings.



#include "UI/InGame/InGameMenu/InGameMenuTab.h"
#include "UI/InGame/InGameMenu/InGameMenuUI.h"
#include "UI/InGame/InGameMenu/InGameMenuTabList.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/MenuAnchor.h"

void UInGameMenuTab::NativeConstruct()
{
	Super::NativeConstruct();
	TabButton->OnClicked.AddUniqueDynamic(this, &UInGameMenuTab::OnTabButtonClicked);
	InGameMenuTabList->SetVisibility(ESlateVisibility::Hidden);
	InGameMenuTabList->InGameMenuTab = this;
}

void UInGameMenuTab::SetTabText(FText Text)
{
	TabTextBlock->SetText(Text);
}

void UInGameMenuTab::OnTabButtonClicked()
{
	ToggleTabList();
}

void UInGameMenuTab::ToggleTabList()
{
	ESlateVisibility State = InGameMenuTabList->GetVisibility();

	if (State == ESlateVisibility::Hidden)
	{
		if(InGameMenuUI)
			InGameMenuUI->CloseAllTabList();
		InGameMenuTabList->Open();
	}
	else if (State == ESlateVisibility::Visible)
	{
		InGameMenuTabList->Close();
	}
}


