// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGame/InventorySlot.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Components/Image.h"


void UInventorySlot::SetItemData(FItemData ItemData)
{
	//슬롯 정보를 업데이트 해준다.


	SlotItemData = ItemData;

	UTexture2D* Texture = ItemData.ItemImage;
	if (IsValid(Texture) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::SetItemData Error. 텍스쳐 정보가 없습니다."));
		return;
	}
	ItemImage->SetBrushFromTexture(Texture, true);
}

void UInventorySlot::Clear()
{
	if (IsValid(DefaultSlotImage) == false)
	{
		UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UInventorySlot::Clear Error. Default Slot Image가 없습니다."));
		return;
	}

	ItemImage->SetBrushFromTexture(DefaultSlotImage, true);

	SlotItemData = FItemData();
}
