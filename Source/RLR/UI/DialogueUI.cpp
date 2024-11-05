// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/InGameMainUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/InventoryManager.h"
#include "Structs/ObjectStructs.h"
#include "Structs/ItemStructs.h"
#include "Kismet/GameplayStatics.h"

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnExit->OnClicked.AddUniqueDynamic(this, &UDialogueUI::OnDialogueEnded);
	BtnQuest->OnClicked.AddUniqueDynamic(this, &UDialogueUI::OnQuestDialogueBegins);
	BtnShop->OnClicked.AddUniqueDynamic(this, &UDialogueUI::OnShopClicked);
	PostButton->OnClicked.AddUniqueDynamic(this, &UDialogueUI::OnPostClicked);

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
	UItemInformation* ItemInformationUI = GetSubUI<UItemInformation>(RLRTAG.UI_ItemInfomation);
	if (!ItemInformationUI) return;

	ItemInformationUI->OpenUI();
	ItemInformationUI->UpdateSlotState(Target);

	InvalidateLayoutAndVolatility();
}

void UDialogueUI::CloseItemInfo()
{
	UItemInformation* ItemInformationUI = GetSubUI<UItemInformation>(RLRTAG.UI_ItemInfomation);
	if (!ItemInformationUI) return;

	ItemInformationUI->CloseUI();
}

void UDialogueUI::AddSaleItem(const FItemData& Item, const FItemResource& NewItemResource)
{
	UNPCShopUI* NPCShopUI = GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
	if (!NPCShopUI) return;

	NPCShopUI->AddSaleItem(Item, NewItemResource);
}

void UDialogueUI::RemoveSaleItem(const FItemData& Item)
{
	UInventoryUI* InventoryUI = GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (!InventoryUI) return;

	InventoryUI->RemoveSaleItem(Item);
}

void UDialogueUI::OnPageActivated()
{
	ChangeInputModeUIOnly();
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}

void UDialogueUI::OnQuestDialogueBegins()
{
	OnQuestDialogueBegin.Broadcast();
	OnDialogueEnd.Broadcast();

	UQuestDialogue* QuestDialogue = GetSubUI<UQuestDialogue>(RLRTAG.UI_Quest_Dialogue);
	if (!QuestDialogue) return;

	QuestDialogue->SetDialogueData(FString::Printf(TEXT("Quest from NPC %d"), CurrentNPCSeq), CurrentNPCSeq, CurrentQuestSeq);
}

void UDialogueUI::OnShopClicked()
{
	if (bOpenShop)
	{
		bOpenShop = false;
		CloseSubUI(RLRTAG.UI_NPCShop);
		CloseSubUI(RLRTAG.UI_Inventory);
	}
	else
	{
		bOpenShop = true;
		auto ObjectManager = GameInstance->GetObjectManager();
		const auto& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);

		UNPCShopUI* NPCShopUI = GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
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

			NPCShopUI->SetItemData(npcData.Shop[0].Items);
			NPCShopUI->SetPosition(panelPos);
			NPCShopUI->OpenUI();
		}

		UInventoryUI* InventoryUI = GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
		if (InventoryUI)
		{
			FVector2D panelPos(100.f + NPCShopUI->RootSizeBox->GetWidthOverride() + 10.f, 100.f);
			InventoryUI->SetPosition(panelPos);
			InventoryUI->OpenUI();
		}
	}
}

void UDialogueUI::OnPostClicked()
{
	if (bOpenPost)
	{
		bOpenPost = false;
		CloseSubUI(RLRTAG.UI_NPCShop);
		CloseSubUI(RLRTAG.UI_Inventory);
		BtnBox->SetVisibility(ESlateVisibility::Visible);
		TxtNPCName->SetVisibility(ESlateVisibility::Visible);
		TxtNPCTalk->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		bOpenPost = true;

		UPostOverlayUI* PostOverlayUI = GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
		if (PostOverlayUI)
		{
			FVector2D panelPos(100.f, 100.f);
			PostOverlayUI->SetPosition(panelPos);
			PostOverlayUI->OpenUI();
			BtnBox->SetVisibility(ESlateVisibility::Hidden);
			TxtNPCName->SetVisibility(ESlateVisibility::Hidden);
			TxtNPCTalk->SetVisibility(ESlateVisibility::Hidden);
		}
		/*
			우편함 UI가 생성될 때 인벤토리 창도 함께 열기
		*/
		UInventoryUI* InventoryUI = GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
		if (InventoryUI)
		{
			FVector2D panelPos(100.f + PostOverlayUI->RootSizeBox->GetWidthOverride() + 10.f, 100.f);
			InventoryUI->SetPosition(panelPos);
			InventoryUI->OpenUI();
		}
	}
}