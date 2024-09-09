// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/Quest/QuestUI/QuestButtonUI.h"
#include "GameManager/GameManager.h"
#include "Components/CanvasPanel.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GameManager/NetworkManager.h"


void UQuestListUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::QUEST);
	SetUITag(FGameplayTagManager::Get().UI_Quest);

	if (CompleteButton)
	{
		CompleteButton->OnClicked.AddDynamic(this, &UQuestListUI::OnCompleteButtonClicked);
	}
	if (DeclineButton)
	{
		DeclineButton->OnClicked.AddDynamic(this, &UQuestListUI::OnDeclineButtonClicked);
	}
	SetBackgroundHitTestVisible(false);
}

void UQuestListUI::UpdateQuestList(const TArray<FQuest>& Quests)
{
	/* TODO : 퀘스트 목록 구성 로직 */
	ClearQuestList();

	for (const FQuest& Quest : Quests)
	{
		AddQuestButton(Quest);
	}
}

void UQuestListUI::ClearQuestList()
{
	if (QuestListContainer)
	{
		QuestListContainer->ClearChildren();
	}
}

void UQuestListUI::AddQuestButton(const FQuest& Quest)
{
	if (GEngine && GEngine->GameViewport)
	{
		UWorld* World = GEngine->GameViewport->GetWorld();
		if (World)
		{
			// 타이머 설정을 게임 스레드에서 실행하도록 람다 사용
			AsyncTask(ENamedThreads::GameThread, [this, World, Quest]()
				{
					if (QuestListContainer && QuestButtonUIClass)
					{
						UQuestButtonUI* QuestButton = CreateWidget<UQuestButtonUI>(this, QuestButtonUIClass);
						if (QuestButton)
						{
							QuestButton->SetQeustInfo(Quest);
							QuestButton->OnQuestButtonClick.AddUObject(this, &UQuestListUI::UpdateQuestDetails);
							QuestListContainer->AddChild(QuestButton);
						}
					}
				});
		}
	}
}

void UQuestListUI::UpdateQuestDetails(const FQuest& Quest)
{
	SelectedQuest = Quest;
	if (SelectedQuestTitle)
	{
		SelectedQuestTitle->SetText(FText::FromString(Quest.QuestTitle));
	}
	if (QuestDescription)
	{
		QuestDescription->SetText(FText::FromString(Quest.QuestDescription));
	}
}

void UQuestListUI::OnQuestButtonClicked(const FQuest& ClickedQuest)
{
	UpdateQuestDetails(ClickedQuest);
}

void UQuestListUI::SetBackgroundHitTestVisible(bool bIsHitTestVisible)
{
	UWidget* RootWidget = GetRootWidget();
	if (UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(RootWidget))
	{
		CanvasPanel->SetVisibility(bIsHitTestVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Visible);
	}
	else if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(RootWidget))
	{
		// 만약 루트 위젯이 CanvasPanel이 아니라면, 첫 번째 자식 위젯을 찾아 설정
		if (PanelWidget->GetChildrenCount() > 0)
		{
			UWidget* FirstChild = PanelWidget->GetChildAt(0);
			FirstChild->SetVisibility(bIsHitTestVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Visible);
		}
	}
}

void UQuestListUI::OnCompleteButtonClicked()
{
	if (SelectedQuest.QuestSeq != 0)
	{
		GameInstance->GetNetworkManager()->SendQuestCompletePacket(SelectedQuest.QuestSeq);
	}
}

void UQuestListUI::OnDeclineButtonClicked()
{
	//TODO : Quest 포기하는 내용 작성 (서버에 전달?)
}