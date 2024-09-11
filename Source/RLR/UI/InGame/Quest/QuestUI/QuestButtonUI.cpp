// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Quest/QuestUI/QuestButtonUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UQuestButtonUI::SetQuestInfo(const FQuest& InQuest)
{
	QuestInfo = InQuest;

	if (QuestNameText)
	{
		QuestNameText->SetText(FText::FromString(QuestInfo.QuestTitle));
	}
}

void UQuestButtonUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (QuestButton)
	{
		QuestButton->OnClicked.AddDynamic(this, &UQuestButtonUI::OnQuestButtonClicked);
	}
}

void UQuestButtonUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetDesiredSizeInViewport(FVector2D(200, 50));
}

void UQuestButtonUI::OnQuestButtonClicked()
{
	OnQuestButtonClick.Broadcast(QuestInfo);
}
