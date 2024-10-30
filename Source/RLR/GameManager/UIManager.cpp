
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/RLRStruct.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "UI/SlotUI.h"
#include "UI/DialogueUI.h"
#include "UI/InGame/BaseScreen.h"
#include "UI/LoadingScreen/LoadingScreen.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/ItemStructs.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "RLR.h"

void UUIManager::OpenMainUI(TSubclassOf<UBaseUI> UIClass)
{
	UpdatedPartyPlayerInfo.Clear();
	UpdatedPlayerInfo.Clear();

	for (USubUI* SubUI : SubUIStack)
	{
		SubUI->RemoveFromParent();
	}
	SubUIStack.Empty();
	UIMap.Empty();

	UBaseScreen* NewScreenUI = CreateWidget<UBaseScreen>(GetWorld(), UIClass);

	if (NewScreenUI)
	{
		NewScreenUI->AddToViewport();
		BaseScreen = NewScreenUI;
		BaseScreen->SetInputMode();

		Pages.Add(BaseScreen->GetPage(EUIType::INGAME_PAGE));
		Pages.Add(BaseScreen->GetPage(EUIType::DIALOGUE_PAGE));

		ARLRPlayerCharacter* playerCharacter = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (playerCharacter)
		{
			BaseScreen->SetActionSystemComponent(playerCharacter);
		}

		FString CurrentLevelName = GetWorld()->GetMapName();
		if (CurrentLevelName.Contains(TEXT("Main")))
		{
			// UI가 완전히 로드된 후에만 네트워크 패킷 처리
			if (GameInstance)
			{
				GameInstance->GetNetworkManager()->SendServerRequest();
				GameInstance->GetNetworkManager()->SendUserQuestPacket();
				GameInstance->GetNetworkManager()->SendInventoryPacket();
			}
		}
	};
}

UBaseUI* UUIManager::OpenUI(EUIType UIType)
{
	//UI Toggle
	UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
	if (!MainUI) return nullptr;

	USubUI* SubUI = MainUI->GetSubUI(UIType);
	if(IsValid(SubUI) == false)
		return nullptr;
	bool bOpen = SubUI->GetVisibility() == ESlateVisibility::Hidden;
	SubUI->OpenUI();

	if (bOpen)
	{
		SubUIStack.AddUnique(SubUI);
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
		CanvasSlot->SetZOrder(SubUIStack.Num());
	}
	else
	{
		SubUIStack.Remove(SubUI);
		SubUIStack.AddUnique(SubUI);
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
		CanvasSlot->SetZOrder(SubUIStack.Num());
	}

	MainUI->InvalidateLayoutAndVolatility();

	return SubUI;
}

void UUIManager::OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType)
{
	/*
		1. itemInfo SubUI 토글
		3. 상태(아이템 정보, 위치) 업데이트
	*/
	auto activePageType = BaseScreen->GetActivePage();

	if (activePageType == EUIType::DIALOGUE_PAGE)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
		if (!DialogueUI) return;

		DialogueUI->OpenItemInfo(Target);
	}
	else
	{
		if (GetMainUI()->SubUIMap.Contains(SubUIType) == false)
			return;

		USubUI* SubUI = GetMainUI()->SubUIMap[SubUIType];
		SetZOrderToTop(SubUI);
		SubUI->OpenUI();
		SubUI->UpdateSlotState(Target);
	}
}

void UUIManager::SetZOrderToTop(USubUI* Target)
{
	if(SubUIStack.Num() == 0)
		return;

	if (SubUIStack[0] != Target && SubUIStack.Find(Target) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UIManager::SetZOrderToTop Error."));
		return;
	}

	SubUIStack.Remove(Target);
	SubUIStack.AddUnique(Target);

	//변경된 순서에 맞게 ZOrder 수정
	AdjustZOrder();
}

void UUIManager::CloseFrontSubUI()
{
	if(SubUIStack.Num() <= 0)
		return;

	FGameplayTag UITag = SubUIStack.Last()->GetUITag();
	ToggleSubUI(UITag);
}

void UUIManager::CloseAllSubUI()
{
	TArray<USubUI*> TempArray = SubUIStack;

	for (USubUI* SubUI : TempArray)
	{
		SubUI->CloseUI();
	}
}

UMainUI* UUIManager::GetMainUI()
{
	return GetPage<UMainUI>(EUIType::INGAME_PAGE);
}

UBaseUI* UUIManager::GetUI(EUIType UIType)
{
	if (UIMap.Contains(UIType) == false)
	{
		DEBUG_MESSAGE;
		return nullptr;
	}

	return UIMap[UIType];
}

void UUIManager::AddUI(UBaseUI* BaseUI)
{
	if(BaseUI->GetUIType() == EUIType::NONE)
		return;

	EUIType Type = BaseUI->GetUIType();
	if (UIMap.Contains(Type) == true)
	{
		//중복된 UI가 추가되고 있다.
		UBaseUI* DeplicatedUI = UIMap[Type];
		DeplicatedUI->RemoveFromParent();
		UIMap.Remove(Type);
		DEBUG_MESSAGE;
	}
	UIMap.Add(Type, BaseUI);
}

void UUIManager::ToggleSubUI(FGameplayTag UITag)
{
	//ESC 누르면 제일 앞에 있는 UI 닫기. 단, 에디터에서는 ESC누르면 게임이 꺼지니 '0'번 키로 설정.
	if (UITag == FGameplayTagManager::Get().UI_Close)
	{
		CloseFrontSubUI();
		return;
	}

	//UI Toggle
	UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
	if (!MainUI) return;
	bool bOpen = MainUI->ToggleSubUI(UITag);

	if (bOpen)
	{
		//열렸으면 Stack에 추가 -> ZOrder조정
		SubUIStack.AddUnique(MainUI->GetSubUI(UITag));
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
		CanvasSlot->SetZOrder(SubUIStack.Num());
	}
	else
	{
		//닫혔으면 Stack에서 제거 -> ZOrder 조정
		SubUIStack.Remove(MainUI->GetSubUI(UITag));
		AdjustZOrder();
	}

	MainUI->InvalidateLayoutAndVolatility();
}

void UUIManager::OpenSubUI(FGameplayTag UITag)
{
	auto activePageType = BaseScreen->GetActivePage();

	if (activePageType == EUIType::DIALOGUE_PAGE)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
		if (!DialogueUI) return;

		DialogueUI->CloseItemInfo();
	}
	else
	{
		UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
		if (!MainUI) return;

		if (!MainUI->IsOpenSubUI(UITag))
		{
			MainUI->OpenSubUI(UITag);
			SubUIStack.AddUnique(MainUI->GetSubUI(UITag));
			AdjustZOrder();
		}
	}
}

void UUIManager::CloseSubUI(FGameplayTag UITag)
{
	auto activePageType = BaseScreen->GetActivePage();

	if (activePageType == EUIType::DIALOGUE_PAGE)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
		if (!DialogueUI) return;

		DialogueUI->CloseItemInfo();
	}
	else
	{
		UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
		if (!MainUI) return;

		if (MainUI->IsOpenSubUI(UITag))
		{
			MainUI->CloseSubUI(UITag);
			SubUIStack.Remove(MainUI->GetSubUI(UITag));
			AdjustZOrder();
		}
	}
}

void UUIManager::CloseSubUI(EUIType SubUIType)
{
	auto activePageType = BaseScreen->GetActivePage();

	if (activePageType == EUIType::DIALOGUE_PAGE)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
		if (!DialogueUI) return;

		DialogueUI->CloseItemInfo();
	}
	else
	{
		UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
		if (!MainUI) return;

		if (GetMainUI()->SubUIMap.Contains(SubUIType) == false)
			return;

		USubUI* SubUI = GetMainUI()->SubUIMap[SubUIType];
		SubUI->SetVisibility(ESlateVisibility::Hidden);
		SubUIStack.Remove(SubUI);
		AdjustZOrder();
		MainUI->InvalidateLayoutAndVolatility();
	}
}

USubUI* UUIManager::GetSubUI(FGameplayTag UITag)
{
	UMainUI* MainUI = GetPage<UMainUI>(EUIType::INGAME_PAGE);
	if (!MainUI) return nullptr;

	return MainUI->GetSubUI(UITag);
}

void UUIManager::AdjustZOrder()
{
	for (int32 OrderNum = 0; OrderNum < SubUIStack.Num(); OrderNum++)
	{
		USubUI* SubUI = SubUIStack[OrderNum];

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUI->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetZOrder(OrderNum);
		}
	}
}

void UUIManager::SetSubUIPosition(FGameplayTag UITag, FVector2D NewPos)
{
	USubUI* subUI = GetMainUI()->GetSubUI(UITag);
	if (!subUI) return;

	auto panel = Cast<UCanvasPanelSlot>(subUI->Slot);
	if (!panel) return;

	panel->SetPosition(NewPos);
}

TObjectPtr<UBaseUI> UUIManager::CreateUI(FString WidgetName)
{
	TSubclassOf<UBaseUI> WidgetClass = GameInstance->GetDataManager()->GetWidgetClass<UBaseUI>(WidgetName);
	if(IsValid(WidgetClass) == false)
		return nullptr;

	UBaseUI* NewUI = CreateWidget<UBaseUI>(GetWorld(), WidgetClass);
	if(IsValid(NewUI) == false)
		return nullptr;
	NewUI->AddToViewport();
	
	return NewUI;
}

TObjectPtr<UDialogueUI> UUIManager::OpenDialogue(TSubclassOf<UBaseUI> UIClass)
{
	UDialogueUI* newDialogueUI = CreateWidget<UDialogueUI>(GetWorld(), UIClass);
	if (!newDialogueUI) return nullptr;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		playerController->SetInputMode(FInputModeUIOnly());
	}

	BaseScreen->SetDialogueUI(newDialogueUI);
	BaseScreen->SetActivePage(EUIType::DIALOGUE_PAGE);

	return GetDialogue();
}

TObjectPtr<UDialogueUI> UUIManager::GetDialogue()
{
	return GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
}

void UUIManager::AddSaleItem(const FItemData& Item, const FItemResource& ItemResource)
{
	if (BaseScreen->GetActivePage() != EUIType::DIALOGUE_PAGE) return;

	UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
	if (!DialogueUI) return;

	DialogueUI->AddSaleItem(Item, ItemResource);
}

void UUIManager::RemoveSaleItem(const FItemData& Item)
{
	if (BaseScreen->GetActivePage() != EUIType::DIALOGUE_PAGE) return;

	UDialogueUI* DialogueUI = GetPage<UDialogueUI>(EUIType::DIALOGUE_PAGE);
	if (!DialogueUI) return;

	DialogueUI->RemoveSaleItem(Item);
}

void UUIManager::OnDialogueEnded()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		FInputModeGameAndUI inputMode = FInputModeGameAndUI();
		inputMode.SetHideCursorDuringCapture(false);

		playerController->SetInputMode(inputMode);
	}

	BaseScreen->SetActivePage(EUIType::INGAME_PAGE);
}