// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/StorageUI.h"
#include "UI/InGame/Storage/StorageTab.h"
#include "UI/Components/WidgetSwitcherButton.h"
#include "Structs/ItemStructs.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "RLR.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"


void UStorageUI::NativeConstruct()
{
	Super::NativeConstruct();

	//BtnBox에 존재하는 WidgetSwitcherBtn 저장
	TabButtons.Empty();
	WidgetTree->GetChildWidgets(BtnBox, TabButtons);
}

//창고 Open시 모든 아이템 Slot 설정
void UStorageUI::SetStorageItems(const TArray<TArray<FItemData>>& StorageItems)
{
	Items = StorageItems;
	SetUnLockedPageNum();
	RefreshUI();
}

void UStorageUI::SetUnLockedPageNum()
{
	UnLockedPageNum = Items.Num();

	for (int i = 0; i < MaxStoragePageNum; i++)
	{
		if (i < UnLockedPageNum) TabButtons[i]->SetIsEnabled(true);
		else TabButtons[i]->SetIsEnabled(false);
	}
}

void UStorageUI::RefreshUI()
{
	for (int i = 0; i < Items.Num(); i++)
	{
		UStorageTab* CurrentTab = Cast<UStorageTab>(WidgetSwitcher->GetWidgetAtIndex(i));
		if (!CurrentTab)
		{
			RLR_LOG(LogRLR, Log, TEXT("StorageTab 형식 불일치"));
			continue;
		}

		CurrentTab->UpdateAllItem(Items[i]);
	}
}