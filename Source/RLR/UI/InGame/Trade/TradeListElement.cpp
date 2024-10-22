// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeListElement.h"
#include "UI/InGame/Trade/TradeListSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"

#include "Structs/ItemStructs.h"

#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"

void UTradeListElement::NativeConstruct()
{
	Super::NativeConstruct();

}

void UTradeListElement::Init()
{
	Super::Init();

}

void UTradeListElement::RefreshUI()
{
	Super::RefreshUI();

	if (TradeListSlot->IsEmpty() == true)
	{
		Clear();
		return;
	}

	const FItemData& Data = TradeListSlot->GetItemData();
	ItemNameText->SetText(Data.NAME);
}

void UTradeListElement::Clear()
{
	Super::Clear();

	TradeListSlot->Clear();
	ItemNameText->SetText(FText());
}

void UTradeListElement::SetItemData(const FItemData& ItemData)
{
	TradeListSlot->SetItemData(ItemData);
	RefreshUI();
}

bool UTradeListElement::IsEmpty()
{
	return TradeListSlot->IsEmpty();
}

void UTradeListElement::SetCanDrag(bool Ret)
{
	IsMySlot = Ret;
	TradeListSlot->SetCanDrag(Ret);
}
