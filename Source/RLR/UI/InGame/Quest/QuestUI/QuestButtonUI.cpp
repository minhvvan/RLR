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
/* TODO : 색상 전환 원하는대로 안됨 */
void UQuestButtonUI::SetButtonState(bool isPressed)
{
	FSlateBrush PressedBrush;
	FSlateBrush NormalBrush;
	if (isPressed)
	{
		PressedBrush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f));
		QuestButton->SetStyle(QuestButton->WidgetStyle);
		QuestButton->WidgetStyle.Normal = PressedBrush;
		QuestButton->WidgetStyle.Hovered = PressedBrush;
		QuestButton->WidgetStyle.Pressed = PressedBrush;
	}
	else
	{
		NormalBrush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
		QuestButton->SetStyle(QuestButton->WidgetStyle);
		QuestButton->WidgetStyle.Normal = NormalBrush;
		QuestButton->WidgetStyle.Hovered = NormalBrush;
		QuestButton->WidgetStyle.Pressed = NormalBrush;
	}
}

FString UQuestButtonUI::GetQuestTitle()
{
	return QuestInfo.QuestTitle;
}

void UQuestButtonUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetButtonState(false);

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
	SetButtonState(true);
	OnQuestButtonClick.Broadcast(QuestInfo, this);
}
