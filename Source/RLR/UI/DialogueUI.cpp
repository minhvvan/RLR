// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueUI.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Quest/Dialogue/QuestDialogue.h"
#include "UI/InGame/Common/DialogueUI/DialogueDynamicButton.h"
#include "UI/InGame/Inventory/ItemInformation.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Storage/StorageUI.h"
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
}

void UDialogueUI::UpdateNPCFunctionality()
{
	UObjectManager* ObjectManager = GameInstance->GetObjectManager();
	const FNPCData& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);
	CreateShopButtons(npcData.Shop);
	CreateQuestButtons(npcData.NPCQuests);

	int npcFuntions = npcData.Functionality;
	for (int i = 0; i < (int)ENPCFunctionality::SIZE; i++)
	{
		//기능 소유 확인
		if (npcFuntions & (1 << i))
		{
			UDialogueDynamicButton* NewButton = CreateDynamicButton();
			NewButton->SetButtonType(i);
			NewButton->SetButtonText(ButtonText[(ENPCFunctionality)i]);
			NewButton->OnButtonClickedSendType.AddUniqueDynamic(this, &UDialogueUI::HandleButtonClicked);

			BtnBox->AddChildToHorizontalBox(NewButton);
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

void UDialogueUI::CreateShopButtons(const TArray<FNPCShop>& ShopData)
{
	for (int i = 0; i < ShopData.Num(); i++)
	{
		UDialogueDynamicButton* NewButton = CreateDynamicButton();
		NewButton->SetButtonText("Shop");
		NewButton->SetButtonIndex(i);
		NewButton->OnButtonClickedSendIndex.AddUniqueDynamic(this, &UDialogueUI::OnShopClicked);

		BtnBox->AddChildToHorizontalBox(NewButton);
	}
}

void UDialogueUI::CreateQuestButtons(const TArray<FQuest>& QuestData)
{
	for (int i = 0; i < QuestData.Num(); i++)
	{
		UDialogueDynamicButton* NewButton = CreateDynamicButton();
		NewButton->SetButtonText("Quest");
		NewButton->SetButtonIndex(i);
		NewButton->OnButtonClickedSendIndex.AddUniqueDynamic(this, &UDialogueUI::OnQuestDialogueBegins);

		NewButton->SetQuestSeq(QuestData[i].QuestSeq);
		QuestButtons.Add(NewButton);

		BtnBox->AddChildToHorizontalBox(NewButton);
	}
}

/* NPC 기능들 동적 생성 */
UDialogueDynamicButton* UDialogueUI::CreateDynamicButton()
{
	if (!DialogueDynamicButtonClass) return nullptr;
	UDialogueDynamicButton* NewButton = CreateWidget<UDialogueDynamicButton>(GetWorld(), DialogueDynamicButtonClass);

	return NewButton;
}

/* 클릭 이벤트(Shop, Quest 제외) */
void UDialogueUI::HandleButtonClicked(int32 ButtonType)
{
	switch (ButtonType)
	{
	case (int)ENPCFunctionality::POST:
		OnPostClicked();
		break;
	case (int)ENPCFunctionality::STORAGE:
		OnStorageClicked();
		break;
	default:
		break;
	}
}

void UDialogueUI::CloseQuestDialogue()
{
	//bOpenQuestDialogue = false;
	CloseSubUI(RLRTAG.UI_Quest_Dialogue);
	ToggleNpcButtons(true);
}

void UDialogueUI::RemoveQuestButton(int32 QuestSeq)
{
	CloseQuestDialogue();

	/* 최근 열었던 QuestButton 삭제 */
	for (int32 i = 0; i < QuestButtons.Num(); i++)
	{
		if (QuestButtons[i] && QuestButtons[i]->GetQuestSeq() == QuestSeq)
		{
			QuestButtons.RemoveAt(i);
			break;
		}
	}
}

void UDialogueUI::RemoveFromHorizontalBox()
{
	CloseQuestDialogue();

	/* 최근 열었던 QuestButton 삭제 */
	for (int32 i = 0; i < QuestButtons.Num(); i++)
	{
		if (QuestButtons[i] && QuestButtons[i]->GetButtonIndex() == CurrentOpenQuest)
		{
			// 버튼을 부모 컨테이너에서 제거
			BtnBox->RemoveChild(QuestButtons[i]);
			break;
		}
	}
}

void UDialogueUI::OpenInventory(FVector2D InventoryPosition)
{
	UInventoryUI* InventoryUI = GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (InventoryUI)
	{
		InventoryUI->SetPosition(InventoryPosition);
		InventoryUI->OpenUI();
	}
}

void UDialogueUI::ReAddQuestButton(int32 QuestSeq)
{
	for (UDialogueDynamicButton* QuestButton : QuestButtons)
	{
		if (QuestButton->GetQuestSeq() == QuestSeq)
		{
			// BtnBox에 버튼 다시 추가
			BtnBox->AddChildToHorizontalBox(QuestButton);
			QuestButton->OnButtonClickedSendIndex.AddUniqueDynamic(this, &UDialogueUI::OnQuestDialogueBegins);
			break;
		}
	}
}

void UDialogueUI::OnPageActivated()
{
	ChangeInputModeUIOnly();
}

void UDialogueUI::ToggleNpcButtons(bool bOpen)
{
	if (bOpen)
	{
		BtnBox->SetVisibility(ESlateVisibility::Visible);
		TxtNPCName->SetVisibility(ESlateVisibility::Visible);
		TxtNPCTalk->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BtnBox->SetVisibility(ESlateVisibility::Hidden);
		TxtNPCName->SetVisibility(ESlateVisibility::Hidden);
		TxtNPCTalk->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UDialogueUI::OnDialogueEnded()
{
	OnDialogueEnd.Broadcast();
}

void UDialogueUI::OnQuestDialogueBegins(int32 ButtonIndex)
{
	UQuestDialogue* QuestDialogueUI = GetSubUI<UQuestDialogue>(RLRTAG.UI_Quest_Dialogue);
	if (!QuestDialogueUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("QuestDialogueUI is nullptr"));
		return;
	}

	if (IsOpenSubUI(RLRTAG.UI_Quest_Dialogue))
	{
		CloseSubUI(RLRTAG.UI_Quest_Dialogue);
		ToggleNpcButtons(true);
	}
	else
	{
		FVector2D panelPos(100.f, 100.f);
		QuestDialogueUI->SetPosition(panelPos);
		QuestDialogueUI->OpenUI();

		QuestDialogueUI->OnQuestDialogueEnd.AddUniqueDynamic(this, &UDialogueUI::CloseQuestDialogue);
		QuestDialogueUI->OnQuestAccept.AddUniqueDynamic(this, &UDialogueUI::RemoveFromHorizontalBox);

		ToggleNpcButtons(false);

		CurrentOpenQuest = ButtonIndex;
	}
}

void UDialogueUI::OnShopClicked(int32 ButtonIndex)
{
	UNPCShopUI* NPCShopUI = GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
	if (!NPCShopUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("NPCShopUI is nullptr"));
		return;
	}

	if (IsOpenSubUI(RLRTAG.UI_NPCShop))
	{
		CloseSubUI(RLRTAG.UI_NPCShop);
		CloseSubUI(RLRTAG.UI_Inventory);
	}
	else
	{
		auto ObjectManager = GameInstance->GetObjectManager();
		const auto& npcData = ObjectManager->GetNPCDataBySeq(CurrentNPCSeq);

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

		FVector2D inventoryPos(100.f + NPCShopUI->RootSizeBox->GetWidthOverride() + 10.f, 100.f);
		OpenInventory(inventoryPos);
	}
}

void UDialogueUI::OnPostClicked()
{
	UPostOverlayUI* PostOverlayUI = GetSubUI<UPostOverlayUI>(RLRTAG.UI_Post);
	if (!PostOverlayUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("PostOverlayUI is nullptr"));
		return;
	}

	if(IsOpenSubUI(RLRTAG.UI_Post))
	{
		CloseSubUI(RLRTAG.UI_NPCShop);
		CloseSubUI(RLRTAG.UI_Inventory);
		ToggleNpcButtons(true);
	}
	else
	{
		FVector2D panelPos(100.f, 100.f);
		PostOverlayUI->SetPosition(panelPos);
		PostOverlayUI->OpenUI();
		ToggleNpcButtons(false);

		/*
			우편함 UI가 생성될 때 인벤토리 창도 함께 열기
		*/
		FVector2D inventoryPos(100.f + PostOverlayUI->RootSizeBox->GetWidthOverride() + 10.f, 100.f);
		OpenInventory(inventoryPos);
	}
}

void UDialogueUI::OnStorageClicked()
{
	UStorageUI* StorageUI = GetSubUI<UStorageUI>(RLRTAG.UI_Storage);
	if (!StorageUI)
	{
		RLR_LOG(LogRLR, Log, TEXT("StorageUI is nullptr"));
		return;
	}

	if (IsOpenSubUI(RLRTAG.UI_Storage))
	{
		CloseSubUI(RLRTAG.UI_Storage);
		CloseSubUI(RLRTAG.UI_Inventory);
		ToggleNpcButtons(true);
	}
	else
	{
		FVector2D panelPos(100.f, 100.f);
		StorageUI->SetPosition(panelPos);
		StorageUI->OpenUI();
		ToggleNpcButtons(false);

		/*
			우편함 UI가 생성될 때 인벤토리 창도 함께 열기
		*/
		FVector2D inventoryPos(100.f + StorageUI->RootSizeBox->GetWidthOverride() + 10.f, 100.f);
		OpenInventory(inventoryPos);
	}
}