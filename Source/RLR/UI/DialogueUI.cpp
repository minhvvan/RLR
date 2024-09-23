// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/InventoryManager.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Structs/ObjectStructs.h"
#include "Structs/ItemStructs.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/Inventory/InventoryUI.h"

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnExit->OnClicked.AddDynamic(this, &UDialogueUI::OnDialogueEnded);
	BtnQuest->OnClicked.AddDynamic(this, &UDialogueUI::OnQuestDialogueBegins);
	BtnShop->OnClicked.AddDynamic(this, &UDialogueUI::OnShopClicked);

	bOpenShop = false;
}

void UDialogueUI::SetDialogueData(FString DialogueString)
{
	//TODO: 대화 UI가 어떻게 될지에 따라 변경해야 함
	TxtNPCTalk->SetText(FText::FromString(DialogueString));
}

void UDialogueUI::SetNPCData(int32 NPCSeq, int32 QuestSeq)
{
	CurrentNPCSeq = NPCSeq;
	CurrentQuestSeq = QuestSeq;
}

void UDialogueUI::OpenItemInfo(USlotUI* Target)
{
	ItemInformationUI->OpenUI();
	ItemInformationUI->UpdateSlotState(Target);

	InvalidateLayoutAndVolatility();
}

void UDialogueUI::CloseItemInfo()
{
	ItemInformationUI->CloseUI();
}

void UDialogueUI::AddSaleItem(const FItemData& Item, const FItemResource& NewItemResource)
{
	NPCShopUI->AddSaleItem(Item, NewItemResource);
}

void UDialogueUI::RemoveSaleItem(const FItemData& Item)
{
	InventoryUI->RemoveSaleItem(Item);
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
	if (bOpenShop)
	{
		bOpenShop = false;
		NPCShopUI->CloseUI();
		InventoryUI->CloseUI();
	}
	else
	{
		bOpenShop = true;
		auto ObjectManager = GameInstance->GetObjectManager();
		const auto& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);

		if (NPCShopUI)
		{
			FVector2D panelPos(100.f, 100.f);

			TArray<FItemResource> ItemResources;
			for (const FItemData& item : npcData.Shop[0].Items)
			{
				FItemResource itemResource;
				itemResource.MakeShopItemResource(item);
				ItemResources.Add(itemResource);
			}

			NPCShopUI->SetItemData(npcData.Shop[0].Items, ItemResources);
			NPCShopUI->SetPosition(panelPos);
			NPCShopUI->OpenUI();
		}

		if (InventoryUI)
		{
			FVector2D panelPos(100.f + NPCShopUI->RootSizeBox->WidthOverride + 10.f, 100.f);
			InventoryUI->SetPosition(panelPos);
			InventoryUI->OpenUI();
		}
	}
}
