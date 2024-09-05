// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnTest->OnClicked.AddDynamic(this, &UDialogueUI::OnDialogueEnded);
	BtnQuest->OnClicked.AddDynamic(this, &UDialogueUI::OnQuestDialogueBegins);
	BtnShop->OnClicked.AddDynamic(this, &UDialogueUI::OnShopClicked);
}

void UDialogueUI::SetDialogueData(FString DialogueString)
{
	//TODO: 대화 UI가 어떻게 될지에 따라 변경해야 함
	TxtTest->SetText(FText::FromString(DialogueString));
}

void UDialogueUI::SetNPCData(int32 NPCSeq, int32 QuestSeq)
{
	CurrentNPCSeq = NPCSeq;
	CurrentQuestSeq = QuestSeq;
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}

void UDialogueUI::OnQuestDialogueBegins()
{
	OnQuestDialogueBegin.Broadcast();
	OnDialogueEnd.Broadcast();

	if (QuestDialogueWidgetClass)
	{
		UQuestDialogue* QuestDialogueWidget = CreateWidget<UQuestDialogue>(GetWorld(), QuestDialogueWidgetClass);
		if (QuestDialogueWidget)
		{
			QuestDialogueWidget->SetDialogueData(FString::Printf(TEXT("Quest from NPC %d"), CurrentNPCSeq), CurrentNPCSeq, CurrentQuestSeq);
			QuestDialogueWidget->AddToViewport();
			this->RemoveFromParent();
		}
	}
}

void UDialogueUI::OnShopClicked()
{
	//Test
	for (int i = 0; i < 5; i++)
	{
		FItemData item;
		item.NAME = FText::FromString(FString::Printf(TEXT("Item%d"), i));
		item.SALE_PRICE = i * 10;
		item.ItemImage = ItemImage;

		TestItems.Add(i, item);
	}

	if (ShopUIClass)
	{
		auto ShopUI = CreateWidget<UNPCShopUI>(GetWorld(), ShopUIClass);
		if (ShopUI)
		{
			ShopUI->SetItemData(TestItems);
			auto slot = Cast<UCanvasPanelSlot>(Canvas->AddChild(ShopUI));
			slot->SetSize({ 600.f, 800.f });
		}
	}
}