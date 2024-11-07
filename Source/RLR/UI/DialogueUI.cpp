// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/InGame/Common/DialogueUI/DialogueDynamicButton.h"
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

	BtnExit->OnClicked.AddDynamic(this, &UDialogueUI::OnDialogueEnded);
	bOpenShop = false;
}

void UDialogueUI::UpdateNPCFunctionality()
{
	UObjectManager* ObjectManager = GameInstance->GetObjectManager();
	const FNPCData& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);

	if (!npcData.Shop.IsEmpty())
	{
		for (int i = 0; i < npcData.Shop.Num(); i++)
		{
			CreateDynamicButton(0, TEXT("Shop"), i);
		}
	}
	if (npcData.hasPostFunctionality)
	{
		/* 우편 기능은 한개밖에 없으니 0으로 ButtonIdx 고정 */
		CreateDynamicButton(1, TEXT("Post"), 0);
	}
	if (!npcData.NPCQuests.IsEmpty())
	{
		for (int i = 0; i < npcData.NPCQuests.Num(); i++)
		{
			CreateDynamicButton(2, TEXT("Quest"), i);
		}
	}
}

void UDialogueUI::SetDialogueData(FString DialogueString)
{
	//TODO: 대화 UI가 어떻게 될지에 따라 변경해야 함
	TxtNPCTalk->SetText(FText::FromString(DialogueString));
}

void UDialogueUI::SetNPCData(int32 NPCSeq)
{
	CurrentNPCSeq = NPCSeq;
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
/* NPC 기능들 동적 생성 */
void UDialogueUI::CreateDynamicButton(int32 ButtonType, FString ButtonText, int32 ButtonIndex)
{
	if(!DialogueDynamicButtonClass) return;
	UDialogueDynamicButton* NewButton = CreateWidget<UDialogueDynamicButton>(GetWorld(), DialogueDynamicButtonClass);

	if(!NewButton) return;
	NewButton->SetButtonType(ButtonType);
	NewButton->SetButtonText(ButtonText);
	NewButton->SetButtonIndex(ButtonIndex);
	NewButton->OnButtonClickedTwoParam.AddDynamic(this, &UDialogueUI::HandleButtonClicked);

	BtnBox->AddChildToHorizontalBox(NewButton);
}
/* 클릭 이벤트 */
void UDialogueUI::HandleButtonClicked(int32 ButtonType, int32 ButtonIdx)
{
	switch (ButtonType)
	{
	case 0 :
		OnShopClicked(ButtonIdx);
		break;
	case 1 : 
		OnPostClicked();
		break;
	case 2 : 
		OnQuestDialogueBegins(ButtonIdx);
		break;
	default:
		break;
	}
}

void UDialogueUI::OnPageActivated()
{
	ChangeInputModeUIOnly();
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}

void UDialogueUI::OnQuestDialogueBegins(int32 ButtonIndex)
{
	OnQuestDialogueBegin.Broadcast();
	OnDialogueEnd.Broadcast();

	if (QuestDialogueWidgetClass)
	{
		UQuestDialogue* QuestDialogueWidget = CreateWidget<UQuestDialogue>(GetWorld(), QuestDialogueWidgetClass);
		if (QuestDialogueWidget)
		{
			auto ObjectManager = GameInstance->GetObjectManager();
			const FNPCData& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);

			// ButtonIndex에 해당하는 Quest 데이터를 가져옴
			if (npcData.NPCQuests.IsValidIndex(ButtonIndex))
			{
				const FQuest& QuestData = npcData.NPCQuests[ButtonIndex];
				FString QuestDialogueString = FString::Printf(TEXT("Quest: %s"), *QuestData.QuestDescription);
				QuestDialogueWidget->SetDialogueData(QuestDialogueString, CurrentNPCSeq, npcData.NPCQuests[ButtonIndex].QuestSeq);
			}

			QuestDialogueWidget->AddToViewport();
			this->RemoveFromParent();
		}
	}
}

void UDialogueUI::OnShopClicked(int32 ButtonIndex)
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
			for (const FItemData& item : npcData.Shop[ButtonIndex].Items)
			{
				FItemResource itemResource;
				itemResource.MakeShopItemResource(item);
				ItemResources.Add(itemResource);
			}

			NPCShopUI->SetItemData(npcData.Shop[ButtonIndex].Items);
			NPCShopUI->SetShopData(npcData.Shop[ButtonIndex]);
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