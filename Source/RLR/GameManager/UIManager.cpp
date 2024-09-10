
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/UIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "UI/SlotUI.h"
#include "UI/DialogueUI.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameManager/RLRStruct.h"
#include "Kismet/GameplayStatics.h"
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

	UMainUI* NewMainUI = CreateWidget<UMainUI>(GetWorld(), UIClass);
	if (NewMainUI)
	{
		NewMainUI->AddToViewport();
		MainUI = NewMainUI;

		ARLRPlayerCharacter* playerCharacter = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!playerCharacter) return;

		MainUI->SetActionSystemComponent(playerCharacter);
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

void UUIManager::CloseSubUI(EUIType SubUIType)
{
	if (DialogueUI)
	{
		DialogueUI->CloseItemInfo();
	}
	else
	{
		if (GetMainUI()->SubUIMap.Contains(SubUIType) == false)
			return;

		USubUI* SubUI = GetMainUI()->SubUIMap[SubUIType];
		SubUI->CloseUI();
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

	SubUIStack.Last()->CloseUI();
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

void UUIManager::ToggleSubUI(FGameplayTag UITag)
{
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
