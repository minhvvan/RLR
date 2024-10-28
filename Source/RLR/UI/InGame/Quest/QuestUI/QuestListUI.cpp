// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Quest/QuestUI/QuestListUI.h"
#include "UI/InGame/Quest/QuestUI/QuestButtonUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameManager/GameManager.h"
#include "Components/CanvasPanel.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/QuestManager.h"


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

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
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

void UQuestListUI::RemoveCompletedQuest(FQuest CompletedQuest)
{
	/* TODO : 리팩토링 대상 */
	if (GEngine && GEngine->GameViewport)
	{
		UWorld* World = GEngine->GameViewport->GetWorld();
		if (World)
		{
			// 타이머 설정을 게임 스레드에서 실행하도록 람다 사용
			AsyncTask(ENamedThreads::GameThread, [this, World, CompletedQuest]()
				{
					for (auto* ChildWidget : QuestListContainer->GetAllChildren())
					{
						if (UQuestButtonUI* QuestButton = Cast<UQuestButtonUI>(ChildWidget))
						{
							if (QuestButton->GetQuestTitle() == SelectedQuest.QuestTitle)
							{
								QuestListContainer->RemoveChild(QuestButton);
								QuestButton->SetButtonState(false);
								break;
							}
						}
					}
					QuestButtons.Remove(SelectedQuest.QuestTitle);
					SelectedQuest = FQuest();
					UpdateQuestDetails(SelectedQuest);
				});
		}
	}
}

void UQuestListUI::ClearQuestList()
{
	// 메인 게임 스레드에서 실행되도록 보장
	if (!IsInGameThread())
	{
		AsyncTask(ENamedThreads::GameThread, [this]()
			{
				ClearQuestList();
			});
		return;
	}

	// 안전하게 자식 위젯 제거
	if (QuestListContainer)
	{
		TArray<UWidget*> ChildrenToRemove = QuestListContainer->GetAllChildren();
		for (UWidget* Child : ChildrenToRemove)
		{
			if (Child)
			{
				QuestListContainer->RemoveChild(Child);
			}
		}
	}

	// 버튼 배열 비우기
	QuestButtons.Empty();
}

void UQuestListUI::AddQuestButton(const FQuest& Quest)
{
	/* TODO : 리팩토링 대상 */
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
							QuestButton->SetQuestInfo(Quest);
							QuestButton->OnQuestButtonClick.AddUObject(this, &UQuestListUI::OnQuestButtonClicked);
							QuestListContainer->AddChild(QuestButton);
							QuestButtons.Add(Quest.QuestTitle, QuestButton);
						}
					}
				});
		}
	}
}

FReply UQuestListUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsInUI(InGeometry, InMouseEvent))
	{
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

bool UQuestListUI::IsInUI(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	return InGeometry.IsUnderLocation(InMouseEvent.GetScreenSpacePosition());
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
		QuestDescription->SetText(FText::FromString(Quest.QuestText));
	}
}
/* TODO : 색상 전환 원하는대로 안됨 */
void UQuestListUI::OnQuestButtonClicked(const FQuest& ClickedQuest, UQuestButtonUI* QuestButtonUI)
{
	QuestButtonUI->SetButtonState(true);
	if (!SelectedQuest.QuestTitle.IsEmpty())
	{
		SelectedQuestButton->SetButtonState(false);
	}
	UpdateQuestDetails(ClickedQuest);
	SelectedQuestButton = QuestButtonUI;
}

void UQuestListUI::OnCompleteButtonClicked()
{
	/* quest 완료조건 */
	if (SelectedQuest.QuestSeq != 0)
	{
		GameInstance->GetQuestManager()->SelectedQuestInfo = SelectedQuest;
		GameInstance->GetNetworkManager()->SendQuestCompletePacket(SelectedQuest.QuestSeq);

		QuestButtons.Remove(SelectedQuest.QuestTitle);
		SelectedQuestButton = nullptr;
		SelectedQuest = FQuest();
	}
}

void UQuestListUI::OnDeclineButtonClicked()
{
	for (auto* ChildWidget : QuestListContainer->GetAllChildren())
	{
		if (UQuestButtonUI* QuestButton = Cast<UQuestButtonUI>(ChildWidget))
		{
			if (QuestButton->GetQuestTitle() == SelectedQuest.QuestTitle)
			{
				QuestListContainer->RemoveChild(QuestButton);
				QuestButton->SetButtonState(false);
				break;
			}
		}
	}
	QuestButtons.Remove(SelectedQuest.QuestTitle);
	SelectedQuest = FQuest();
	UpdateQuestDetails(SelectedQuest);
}