
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

void UUIManager::OpenMainUI(TSubclassOf<UMainUI> UIClass)
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

void UUIManager::OpenSubUI(USubUI* Target)
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

void UUIManager::OpenSubUINearTargetSlot(USubUI* SubUI, USlotUI* Target)
{
	OpenSubUI(SubUI);
	SetZOrderToTop(SubUI);

	/*
			타깃 슬롯 위에 있는 마우스 커서 위치를 기준으로 UI 창을 띄운다.

			ex)인벤토리에서 아이템 슬롯 위에 커서를 올려두었을 때, 커서 옆에 아이템 정보창을 띄우게 하기 위한 함수로 사용 중.

	*/


	//마우스 커서 위치를 가져온다.
	FVector2D V1  = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	//슬롯의 크기 만큼 위치를 조정해준다.
	V1.X -= Target->RootSizeBox->GetWidthOverride() * 2;


	float SubUIRootBoxWidth= SubUI->RootSizeBox->GetWidthOverride();
	//띄우려는 창의 크기를 고려해서 위치를 조정해준다.
	if (V1.X > SubUIRootBoxWidth)
	{
		V1.X -= SubUIRootBoxWidth /2;
	}
	else
	{
		V1.X += SubUIRootBoxWidth/2 + Target->RootSizeBox->GetWidthOverride() * 4;
	}

	Cast<UCanvasPanelSlot>(SubUI->Slot)->SetPosition(V1);
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
	//ZOrder 100은 MainUI이 맨 앞으로 오게 MainUI의 고정값으로 해둘 예정. 그래서 99로 해둠.
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Target->Slot);
	if (CanvasSlot)
	{
		CanvasSlot->SetZOrder(99);
		//SubUI->InvalidateLayoutAndVolatility();
		SubUIStack.AddUnique(Target);
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
