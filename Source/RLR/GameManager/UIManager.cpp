
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/UIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "UI/MainUI.h"
#include "UI/SubUI.h"

void UUIManager::ShowMainUI(TSubclassOf<UMainUI> UIClass)
{
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
	};

}

void UUIManager::ShowSubUI(USubUI* Target)
{
	if(Target == nullptr)
		return;

	Target->SetVisibility(ESlateVisibility::Visible);
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Target->Slot);

	//제일 최근에 열린 SubUI는 화면에서 제일 앞에 올려준다.
	if (CanvasSlot)
	{
		SubUIStack.AddUnique(Target);
		CanvasSlot->SetZOrder(SubUIStack.Num());
		//Target->InvalidateLayoutAndVolatility();
		MainUI->InvalidateLayoutAndVolatility();
	}

}

void UUIManager::SetZOderUI(USubUI* Target)
{
	//기존에 올라와 있던 UI들을 정리하고,
	for (int32 OrderNum = 0; OrderNum < SubUIStack.Num(); OrderNum++)
	{
		USubUI* SubUI = SubUIStack[OrderNum];

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUI->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetZOrder(OrderNum);
			//SubUI->InvalidateLayoutAndVolatility();
		}
	}

	//지목된 UI를 제일 앞에 올려준다.
	//100은 MainUI의 고정값으로 해둘 예정. 그래서 99로 해둠.
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Target->Slot);
	if (CanvasSlot)
	{
		CanvasSlot->SetZOrder(99);
		//SubUI->InvalidateLayoutAndVolatility();
	}
	MainUI->InvalidateLayoutAndVolatility();
}

void UUIManager::CloseSubUI(USubUI* Target)
{
	Target->SetVisibility(ESlateVisibility::Hidden);
	SubUIStack.Remove(Target);

	for (int32 OrderNum =0 ; OrderNum < SubUIStack.Num(); OrderNum++)
	{
		USubUI* SubUI = SubUIStack[OrderNum];

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUI->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetZOrder(OrderNum);
			//SubUI->InvalidateLayoutAndVolatility();
		}
	}

	MainUI->InvalidateLayoutAndVolatility();
}

void UUIManager::CloseSubUI()
{
}

void UUIManager::CloseAllSubUI()
{
}

UMainUI* UUIManager::GetMainUI()
{
	return MainUI;
}
