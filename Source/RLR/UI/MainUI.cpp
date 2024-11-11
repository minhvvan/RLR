// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "UI/GroupUI.h"
#include "Blueprint/WidgetTree.h"
#include "Structs/UtilStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "RLR.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	BindSubUI();

}

void UMainUI::BindSubUI()
{
	TArray<UWidget*> Array;
	WidgetTree->GetAllWidgets(Array);

	for (auto Widget : Array)
	{
		if (USubUI* SubUI = Cast<USubUI>(Widget))
		{
			SubUI->SetMainUI(this);
			FGameplayTag Tag = SubUI->GetUITag();

			if (Tag == FGameplayTag::EmptyTag)
			{
				RLR_LOG(LogRLR, Log, TEXT("BIndSubUI Error.UITag이 설정이 안된 SubUI가 있습니다.확인 바랍니다. %s"), *SubUI->GetName());
				continue;
			}

			SubUIMap.Add(Tag, SubUI);
		}
		else if (UGroupUI* GroupUI = Cast<UGroupUI>(Widget))
		{
			TArray<USubUI*> SubUIs = GroupUI->GetSubUIs();

			for (auto subUI : SubUIs)
			{
				UCanvasPanelSlot* OldSlot = Cast<UCanvasPanelSlot>(subUI->Slot);
				if (OldSlot && Canvas)
				{
					// CanvasPanel에 SubUI를 추가
					UCanvasPanelSlot* NewSlot = Canvas->AddChildToCanvas(subUI);

					// 이전 슬롯의 Transform 설정을 복제
					NewSlot->SetPosition(OldSlot->GetPosition());
					NewSlot->SetSize(OldSlot->GetSize());
					NewSlot->SetAnchors(OldSlot->GetAnchors());
					NewSlot->SetAlignment(OldSlot->GetAlignment());
					NewSlot->SetOffsets(OldSlot->GetOffsets());
					NewSlot->SetAutoSize(OldSlot->GetAutoSize());
				}

				subUI->SetMainUI(this);
				subUI->SetParent(this);
				SubUIMap.Add(subUI->GetUITag(), subUI);
			}
		}
	}
}

void UMainUI::RefreshUI()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			Super::RefreshUI();
			TArray<UWidget*> Array;
			WidgetTree->GetAllWidgets(Array);
			for (auto Widget : Array)
			{
				if (UBaseUI* ChildUI = Cast<UBaseUI>(Widget))
				{
					ChildUI->RefreshUI();
				}
			}
		});
	
}

bool UMainUI::IsOpenSubUI(FGameplayTag InputTag)
{
	USubUI* subUI = GetSubUI(InputTag);
	if (!subUI) return false;

	return subUI->GetVisibility() == ESlateVisibility::Visible;
}

void UMainUI::ToggleSubUI(FGameplayTag InputTag)
{
	if (IsOpenSubUI(InputTag))
	{
		CloseSubUI(InputTag);
	}
	else
	{
		OpenSubUI(InputTag);
	}

	InvalidateLayoutAndVolatility();
}

void UMainUI::OpenSubUI(FGameplayTag InputTag)
{
	if (IsOpenSubUI(InputTag)) return;

	USubUI* subUI = GetSubUI(InputTag);
	if (!subUI) return;

	SubUIStack.AddUnique(subUI);
	subUI->OpenUI();
	AdjustZOrder();
}

void UMainUI::CloseSubUI(FGameplayTag InputTag)
{
	if (!IsOpenSubUI(InputTag)) return;

	USubUI* subUI = GetSubUI(InputTag);
	if (!subUI) return;

	SubUIStack.Remove(subUI);
	subUI->CloseUI();
	AdjustZOrder();
}

void UMainUI::CloseFrontSubUI()
{
	if (SubUIStack.IsEmpty()) return;

	FGameplayTag subUITag = SubUIStack.Last()->GetUITag();
	CloseSubUI(subUITag);
}

void UMainUI::CloseAllSubUI()
{
	TArray<USubUI*> TempArray = SubUIStack;

	for (USubUI* SubUI : TempArray)
	{
		SubUI->CloseUI();
	}
}

void UMainUI::AdjustZOrder()
{
	for (int32 order = 0; order < SubUIStack.Num(); order++)
	{
		USubUI* SubUI = SubUIStack[order];

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SubUI->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetZOrder(order);
		}
	}
}

void UMainUI::SetZOrderToTop(FGameplayTag Tag)
{
	if (SubUIStack.Num() == 0) return;

	auto* target = GetSubUI<USubUI>(Tag);
	if (!target) return;

	if (SubUIStack[0] != target && SubUIStack.Find(target) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UIManager::SetZOrderToTop Error."));
		return;
	}

	SubUIStack.Remove(target);
	SubUIStack.AddUnique(target);

	//변경된 순서에 맞게 ZOrder 수정
	AdjustZOrder();
}

void UMainUI::SetSubUIPosition(FGameplayTag Tag, FVector2D NewPos)
{
	USubUI* subUI = GetSubUI<USubUI>(Tag);
	if (!subUI) return;

	auto panel = Cast<UCanvasPanelSlot>(subUI->Slot);
	if (!panel) return;

	panel->SetPosition(NewPos);
}

void UMainUI::OpenSubUINearTargetSlot(USlotUI* Target, FGameplayTag Tag)
{
	USubUI* SubUI = GetSubUI(Tag);
	SubUI->UpdateSlotState(Target);

	OpenSubUI(Tag);
	SetZOrderToTop(Tag);
}
