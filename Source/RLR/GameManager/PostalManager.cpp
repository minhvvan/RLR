// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UPostalManager::Update()
{
	OnUpdatePostalDelegateBroadcast();
}

void UPostalManager::AddItem(const FItemData& NewItem)
{
	if (NewItem == FItemData::EmptyItemData)
	{
		return;
	}
	ItemData.Add(NewItem.ITEM_SLOT_IDX, NewItem);
	OnUpdatePostalDelegateBroadcast();
}

void UPostalManager::AddItemList(const TArray<FItemData>& NewItemList, const TArray<FItemResource>& NewItemResourceList)
{
	for (const FItemData& newItem : NewItemList)
	{
		if (newItem == FItemData::EmptyItemData)
		{
			continue;
		}
		ItemData.Add(newItem.ITEM_SLOT_IDX, newItem);
	}
	AddItemResourceList(NewItemResourceList);
}

void UPostalManager::AddItemResourceList(const TArray<FItemResource>& NewItemResourceList)
{
	for (const FItemResource& newItemResource : NewItemResourceList)
	{
		if (newItemResource.ITEM_SEQ == -1)
		{
			continue;
		}
		ItemResourceData.Add(newItemResource.ITEM_SEQ, newItemResource);
	}
}

FItemData UPostalManager::GetItem(int32 ItemSeq)
{
	if (ItemData.Contains(ItemSeq))
	{
		return ItemData[ItemSeq];
	}
	return FItemData::EmptyItemData;
}

void UPostalManager::RemoveItem(int32 ItemSeq)
{
	if(ItemData.Contains(ItemSeq))
	{ 
		FItemData RemoveItem;
		ItemData.RemoveAndCopyValue(ItemSeq, RemoveItem);
		OnUpdatePostalDelegateBroadcast();
	}
}

void UPostalManager::ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex)
{
	if (ItemData.Contains(Item_Seq))
	{
		ItemData[Item_Seq].ITEM_SLOT_IDX = NewSlotIndex;
	}
}

void UPostalManager::GetItemList(UPARAM(ref)TArray<FItemData>& ItemArray)
{
	ItemData.GenerateValueArray(ItemArray);
}

void UPostalManager::GetItemResourceList(UPARAM(ref)TArray<FItemResource>& ItemResourceArray)
{
	ItemResourceData.GenerateValueArray(ItemResourceArray);
}

const FItemResource UPostalManager::GetItemResource(int32 ItemSeq) const
{
	if (ItemResourceData.Contains(ItemSeq))
	{
		return ItemResourceData[ItemSeq];
	}
	return FItemResource::EmptyItemResource;
}

bool UPostalManager::TryGetItemResource(int32 ItemSeq, FItemResource& OutItemResource) const
{
	if (ItemResourceData.Contains(ItemSeq))
	{
		OutItemResource = ItemResourceData[ItemSeq];
		return true;
	}
	OutItemResource = FItemResource::EmptyItemResource;
	return false;
}

void UPostalManager::SetItemList(TArray<FItemData>& ItemArray)
{
	ItemData.Empty();

	for (const FItemData& item : ItemArray)
	{
		ItemData.Add(item.ITEM_SEQ, item);
	}
	Update();
}

void UPostalManager::OnUpdatePostalDelegateBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			OnUpdatePostalDelegate.Broadcast();
		});
}