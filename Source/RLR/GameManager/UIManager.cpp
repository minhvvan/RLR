
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
	MainUI = CreateWidget<UMainUI>(GetWorld(), UIClass);
	if (!MainUI) return;

	MainUI->AddToViewport();
	MainUI->SetInputMode();

	UpdatedPartyPlayerInfo.Clear();
	UpdatedPlayerInfo.Clear();

	for (USubUI* SubUI : SubUIStack)
	{
		SubUI->RemoveFromParent();
	}
	SubUIStack.Empty();
	//UIMap.Empty();

	//ARLRPlayerCharacter* playerCharacter = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (playerCharacter)
	//{
	//	BaseScreen->SetActionSystemComponent(playerCharacter);
	//}

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
}

//UBaseUI* UUIManager::OpenUI(EUIType UIType)
//{
//	//UI Toggle
//	UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
//	if (!currentMainUI) return nullptr;
//
//	USubUI* SubUI = currentMainUI->GetSubUI(UIType);
//	if(IsValid(SubUI) == false)
//		return nullptr;
//
//
//	bool bOpen = SubUI->GetVisibility() == ESlateVisibility::Hidden;
//	SubUI->OpenUI();
//
//	if (bOpen)
//	{
//		SubUIStack.AddUnique(SubUI);
//		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
//		CanvasSlot->SetZOrder(SubUIStack.Num());
//	}
//	else
//	{
//		SubUIStack.Remove(SubUI);
//		SubUIStack.AddUnique(SubUI);
//		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
//		CanvasSlot->SetZOrder(SubUIStack.Num());
//	}
//
//	MainUI->InvalidateLayoutAndVolatility();
//
//	return SubUI;
//}

void UUIManager::OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType)
{
	/*
		1. itemInfo SubUI 토글
		3. 상태(아이템 정보, 위치) 업데이트
	*/
	auto activePageTag = GetActivePageTag();

	if (activePageTag == FGameplayTagManager::Get().Page_Dialogue)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
		if (!DialogueUI) return;

		DialogueUI->OpenItemInfo(Target);
	}
	else
	{
		if (GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame)->SubUIMap.Contains(SubUIType) == false)
			return;

		USubUI* SubUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame)->SubUIMap[SubUIType];
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

//UMainUI* UUIManager::GetMainUI()
//{
//	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
//	if (!BaseScreen) return MainUI;
//
//	return GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
//}

//UBaseUI* UUIManager::GetUI(EUIType UIType)
//{
//	if (UIMap.Contains(UIType) == false)
//	{
//		DEBUG_MESSAGE;
//		return nullptr;
//	}
//
//	return UIMap[UIType];
//}

//void UUIManager::AddUI(UBaseUI* BaseUI)
//{
//	if(BaseUI->GetUIType() == EUIType::NONE)
//		return;
//
//	EUIType Type = BaseUI->GetUIType();
//	if (UIMap.Contains(Type) == true)
//	{
//		//중복된 UI가 추가되고 있다.
//		UBaseUI* DeplicatedUI = UIMap[Type];
//		DeplicatedUI->RemoveFromParent();
//		UIMap.Remove(Type);
//		DEBUG_MESSAGE;
//	}
//	UIMap.Add(Type, BaseUI);
//}

void UUIManager::ToggleSubUI(FGameplayTag UITag)
{
	//ESC 누르면 제일 앞에 있는 UI 닫기. 단, 에디터에서는 ESC누르면 게임이 꺼지니 '0'번 키로 설정.
	if (UITag == FGameplayTagManager::Get().UI_Close)
	{
		CloseFrontSubUI();
		return;
	}

	//UI Toggle
	UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	if (!currentMainUI) return;
	bool bOpen = currentMainUI->ToggleSubUI(UITag);

	if (bOpen)
	{
		//열렸으면 Stack에 추가 -> ZOrder조정
		SubUIStack.AddUnique(currentMainUI->GetSubUI(UITag));
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
		CanvasSlot->SetZOrder(SubUIStack.Num());
	}
	else
	{
		//닫혔으면 Stack에서 제거 -> ZOrder 조정
		SubUIStack.Remove(currentMainUI->GetSubUI(UITag));
		AdjustZOrder();
	}

	currentMainUI->InvalidateLayoutAndVolatility();
}

void UUIManager::OpenSubUI(FGameplayTag UITag)
{
	auto activePageTag = GetActivePageTag();

	if (activePageTag == FGameplayTagManager::Get().Page_Dialogue)
	{
		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
		if (!DialogueUI) return;

		DialogueUI->CloseItemInfo();
	}
	else
	{
		UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
		if (!currentMainUI) return;

		if (!currentMainUI->IsOpenSubUI(UITag))
		{
			currentMainUI->OpenSubUI(UITag);
			SubUIStack.AddUnique(currentMainUI->GetSubUI(UITag));
			AdjustZOrder();
		}
	}
}

void UUIManager::CloseSubUI(FGameplayTag UITag)
{
	auto activePageTag = GetActivePageTag();
	auto currentMainUI = GetPage<UMainUI>(activePageTag);

	if (!currentMainUI) return;
	currentMainUI->CloseSubUI(UITag);

	//if (activePageTag == FGameplayTagManager::Get().Page_Dialogue)
	//{
	//	UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
	//	if (!DialogueUI) return;

	//	DialogueUI->CloseItemInfo();
	//}
	//else
	//{
	//	UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	//	if (!currentMainUI) return;

	//	if (currentMainUI->IsOpenSubUI(UITag))
	//	{
	//		currentMainUI->CloseSubUI(UITag);
	//		SubUIStack.Remove(currentMainUI->GetSubUI(UITag));
	//		AdjustZOrder();
	//	}
	//}
}

//void UUIManager::CloseSubUI(EUIType SubUIType)
//{
//	auto activePageTag = GetActivePageTag();
//
//	if (activePageTag == FGameplayTagManager::Get().Page_Dialogue)
//	{
//		UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
//		if (!DialogueUI) return;
//
//		DialogueUI->CloseItemInfo();
//	}
//	else
//	{
//		UMainUI* currentMainUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
//		if (!currentMainUI) return;
//
//		if (GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame)->SubUIMap.Contains(SubUIType) == false)
//			return;
//
//		USubUI* SubUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame)->SubUIMap[SubUIType];
//		SubUI->SetVisibility(ESlateVisibility::Hidden);
//		SubUIStack.Remove(SubUI);
//		AdjustZOrder();
//		currentMainUI->InvalidateLayoutAndVolatility();
//	}
//}

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
	USubUI* subUI = GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame)->GetSubUI(UITag);
	if (!subUI) return;

	auto panel = Cast<UCanvasPanelSlot>(subUI->Slot);
	if (!panel) return;

	panel->SetPosition(NewPos);
}

//TObjectPtr<UBaseUI> UUIManager::CreateUI(FString WidgetName)
//{
//	TSubclassOf<UBaseUI> WidgetClass = GameInstance->GetDataManager()->GetWidgetClass<UBaseUI>(WidgetName);
//	if(IsValid(WidgetClass) == false)
//		return nullptr;
//
//	UBaseUI* NewUI = CreateWidget<UBaseUI>(GetWorld(), WidgetClass);
//	if(IsValid(NewUI) == false)
//		return nullptr;
//	NewUI->AddToViewport();
//	
//	return NewUI;
//}

TObjectPtr<UDialogueUI> UUIManager::OpenDialogue(TSubclassOf<UBaseUI> UIClass)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return nullptr;

	UBaseUI* newDialougePage = CreateWidget<UBaseUI>(GetWorld(), UIClass);
	if (!BaseScreen->SetPageUI(FGameplayTagManager::Get().Page_Dialogue, newDialougePage)) return nullptr;

	BaseScreen->SetActivePage(FGameplayTagManager::Get().Page_Dialogue);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		playerController->SetInputMode(FInputModeUIOnly());
	}

	return GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
}

FGameplayTag UUIManager::GetActivePageTag()
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return FGameplayTag::EmptyTag;
	return BaseScreen->GetActivePage();
}

void UUIManager::AddSaleItem(const FItemData& Item, const FItemResource& ItemResource)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return;

	if (BaseScreen->GetActivePage() != FGameplayTagManager::Get().Page_Dialogue) return;

	UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
	if (!DialogueUI) return;

	DialogueUI->AddSaleItem(Item, ItemResource);
}

void UUIManager::RemoveSaleItem(const FItemData& Item)
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return;

	if (BaseScreen->GetActivePage() != FGameplayTagManager::Get().Page_Dialogue) return;

	UDialogueUI* DialogueUI = GetPage<UDialogueUI>(FGameplayTagManager::Get().Page_Dialogue);
	if (!DialogueUI) return;

	DialogueUI->RemoveSaleItem(Item);
}

void UUIManager::OnDialogueEnded()
{
	UBaseScreen* BaseScreen = Cast<UBaseScreen>(MainUI);
	if (!BaseScreen) return;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		FInputModeGameAndUI inputMode = FInputModeGameAndUI();
		inputMode.SetHideCursorDuringCapture(false);

		playerController->SetInputMode(inputMode);
	}

	BaseScreen->SetActivePage(FGameplayTagManager::Get().Page_InGame);
}