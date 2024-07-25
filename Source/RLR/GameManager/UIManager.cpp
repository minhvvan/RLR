
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/UIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "UI/SlotUI.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameManager/RLRStruct.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

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

void UUIManager::OpenSubUINearTargetSlot(USlotUI* Target)
{
	/*
		1. itemInfo SubUI 토글
		3. 상태(아이템 정보, 위치) 업데이트
	*/
	ToggleSubUI((int)EUIType::ITEMINFO);
	USubUI* SubUI = MainUI->GetSubUI((int)EUIType::ITEMINFO);
	if (!SubUI) return;

	SubUI->UpdateSlotState(Target);
}

void UUIManager::CloseSubUINearTargetSlot()
{
	//itemInfo SubUI 토글
	ToggleSubUI((int)EUIType::ITEMINFO);
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

void UUIManager::ToggleSubUI(int inputID)
{
	//UI Toggle
	bool bOpen = MainUI->ToggleSubUI(inputID);
	
	if (bOpen)
	{
		//열렸으면 Stack에 추가 -> ZOrder조정
		SubUIStack.AddUnique(MainUI->GetSubUI(inputID));
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUIStack.Top()->Slot);
		CanvasSlot->SetZOrder(SubUIStack.Num());
	}
	else
	{
		//닫혔으면 Stack에서 제거 -> ZOrder 조정
		SubUIStack.Remove(MainUI->GetSubUI(inputID));
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
