// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostBundleSend.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"

void UPostBundleSend::NativeConstruct()
{
	BtnConfirm->OnClicked.AddUniqueDynamic(this, &UPostBundleSend::OnConfirmClicked);
	BtnCancel->OnClicked.AddUniqueDynamic(this, &UPostBundleSend::OnCancelClicked);
	BtnIncrease->OnClicked.AddUniqueDynamic(this, &UPostBundleSend::OnIncreaseClicked);
	BtnDecrease->OnClicked.AddUniqueDynamic(this, &UPostBundleSend::OnDecreaseClicked);
}

void UPostBundleSend::OnConfirmClicked()
{
	ConfirmSendPostBundle.Broadcast(Item, slotIndex);
	RemoveFromParent();
}

void UPostBundleSend::OnCancelClicked()
{
	RemoveFromParent();
}

void UPostBundleSend::OnIncreaseClicked()
{
	int32 itemQuantity = Item.ITEM_QUANTITY;
	Item.ITEM_QUANTITY++;
	if (GameInstance->GetInventoryManager()->GetItem(slotIndex).ITEM_QUANTITY < Item.ITEM_QUANTITY)
	{
		Item.ITEM_QUANTITY = itemQuantity;
		return;
	}
	UpdateAmountText();
}

void UPostBundleSend::OnDecreaseClicked()
{
	if (Item.ITEM_QUANTITY == 1) return;
	Item.ITEM_QUANTITY--;
	UpdateAmountText();
}

void UPostBundleSend::UpdateAmountText()
{
	EdtAmount->SetText(FText::AsNumber(Item.ITEM_QUANTITY));
}

void UPostBundleSend::SetSlotIndex(int32 NewSlotIndex)
{
	slotIndex = NewSlotIndex;
}

void UPostBundleSend::SetItemData(const FItemData& item)
{
	Item = item;
	ImgItem->SetBrushFromTexture(Item.GetItemResource().ItemImage);
	UpdateAmountText();
}
