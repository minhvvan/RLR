
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

void UUIManager::OpenMainUI(TSubclassOf<UMainUI> UIClass)
{
	UpdatedPartyPlayerInfo.Clear();
	UpdatedPlayerInfo.Clear();

	for (USubUI* SubUI : SubUIStack)
	{
		SubUI->RemoveFromParent();
	}
	SubUIStack.Empty();
	UIMap.Empty();
	
	UMainUI* NewMainUI = CreateWidget<UMainUI>(GetWorld(), UIClass);
	if (NewMainUI)
	{
		NewMainUI->AddToViewport();
		MainUI = NewMainUI;
		MainUI->SetInputMode();

		ARLRPlayerCharacter* playerCharacter = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (playerCharacter)
			MainUI->SetActionSystemComponent(playerCharacter);

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

void UUIManager::OpenSubUINearTargetSlot(USlotUI* Target, EUIType SubUIType)
{
	/*
		1. itemInfo SubUI 토글
		3. 상태(아이템 정보, 위치) 업데이트
	*/

	//TODO: Swither가 생기면 현재 켜진 곳에서 받아와야 함
	//현재는 임시로 test
	if (DialogueUI)
	{
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

	MainUI->InvalidateLayoutAndVolatility();
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
	return MainUI;
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
	if (DialogueUI)
	{
		DialogueUI->CloseItemInfo();
	}
	else
	{
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
	if (DialogueUI)
	{
		DialogueUI->CloseItemInfo();
	}
	else
	{
		if (MainUI->IsOpenSubUI(UITag))
		{
			MainUI->CloseSubUI(UITag);
			SubUIStack.Remove(MainUI->GetSubUI(UITag));
			AdjustZOrder();
		}
	}
}

USubUI* UUIManager::GetSubUI(FGameplayTag UITag)
{
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

void UUIManager::SetSubUIPos(FGameplayTag UITag, FVector2D NewPos)
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
	if (newDialogueUI)
	{
		DialogueUI = newDialogueUI;
		DialogueUI->OnDialogueEnd.AddDynamic(this, &UUIManager::OnDialogueEnded);

		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController)
		{
			playerController->SetInputMode(FInputModeUIOnly());
		}

		if (MainUI)
		{
			MainUI->SetVisibility(ESlateVisibility::Hidden);
		}

		DialogueUI->AddToViewport();
	};

	return DialogueUI;
}

void UUIManager::AddSaleItem(const FItemData& Item, const FItemResource& ItemResource)
{
	if (!DialogueUI || DialogueUI->GetVisibility() == ESlateVisibility::Hidden) return;
	DialogueUI->AddSaleItem(Item, ItemResource);
}

void UUIManager::RemoveSaleItem(const FItemData& Item)
{
	if (!DialogueUI || DialogueUI->GetVisibility() == ESlateVisibility::Hidden) return;
	DialogueUI->RemoveSaleItem(Item);
}

void UUIManager::OnDialogueEnded()
{
	RLR_LOG(LogRLR, Log, TEXT("DialougeEnd"));
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		FInputModeGameAndUI inputMode = FInputModeGameAndUI();
		inputMode.SetHideCursorDuringCapture(false);

		playerController->SetInputMode(inputMode);
	}

	DialogueUI->RemoveFromParent();
	if (MainUI)
	{
		MainUI->SetVisibility(ESlateVisibility::Visible);
	}
}
