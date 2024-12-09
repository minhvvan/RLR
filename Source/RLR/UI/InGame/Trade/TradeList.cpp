// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Trade/TradeList.h"
#include "UI/InGame/Trade/TradeListElement.h"
#include "UI/InGame/Trade/TradeListSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/LiteralManager.h"

#include "Components/ScrollBox.h"

void UTradeList::NativeConstruct()
{
	Super::NativeConstruct();

}

void UTradeList::Init()
{
	Super::Init();
	TradeListScrollBox->ClearChildren();

	TSubclassOf<UTradeListElement> ElementClass = GetWidgetClass<UTradeListElement>(RLRLITERAL.WBP_TradeListElement);
	if (IsValid(ElementClass) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	for (int32 SlotIndex = 0; SlotIndex < TradeListElementMaxCount; SlotIndex++)
	{
		UTradeListElement* NewElement = CreateWidget<UTradeListElement>(this, ElementClass);
		NewElement->Clear();

		TradeListScrollBox->AddChild(NewElement);
		TradeListElementMap.Add(SlotIndex, NewElement);
	}
}

void UTradeList::RefreshUI()
{
	Super::RefreshUI();

	for (TTuple<int32, UTradeListElement*> Iter : TradeListElementMap)
	{
		int32 SlotIndex = Iter.Key;
		UTradeListElement* Element = Iter.Value;
		Element->RefreshUI();
	}
}

void UTradeList::Clear()
{
	Super::Clear();

	for (TTuple<int32, UTradeListElement*> Iter : TradeListElementMap)
	{
		int32 SlotIndex = Iter.Key;
		UTradeListElement* Element = Iter.Value;
		Element->Clear();
	}
}

void UTradeList::AddTradeItem(const FItemData& NewItem)
{
	for (TTuple<int32, UTradeListElement*> Iter : TradeListElementMap)
	{
		int32 SlotIndex = Iter.Key;
		UTradeListElement* Element = Iter.Value;
	
		if (Element->IsEmpty() == false)
		{
			continue;
		}

		Element->SetItemData(NewItem);
		break;
	}
}

void UTradeList::RemoveTradeItem(int32 RemoveItemID)
{
	for (TTuple<int32, UTradeListElement*> Iter : TradeListElementMap)
	{
		int32 SlotIndex = Iter.Key;
		UTradeListElement* Element = Iter.Value;

		if (Element->IsEmpty() == true)
		{
			continue;
		}

		const FItemData& ItemData = Element->TradeListSlot->GetItemData();
		const int32 ItemID = ItemData.ITEM_ID;
		if (ItemID == RemoveItemID)
		{
			Element->Clear();
			break;
		}
	}
}

void UTradeList::SetCanDrag(bool Ret)
{
	for (TTuple<int32, UTradeListElement*> Iter : TradeListElementMap)
	{
		int32 SlotIndex = Iter.Key;
		UTradeListElement* Element = Iter.Value;
		Element->SetCanDrag(Ret);
	}
}
